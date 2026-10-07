from typing import List, Tuple, Dict, Set
from core.config import Config, Action
from core.utils import *
from core.environment import GridWorld

State = Tuple[int, int, int, int]

class BaseRobotMDP:
    def __init__(self, env: GridWorld):
        self.env = env
        self.config = Config()
        self.num_dirt = len(env.dirt_positions)
        self.cat_influence_zone = env.get_cat_influence_zone()
        self._precompute_redirt_probs()
        self._precompute_move_dists()
        self._transition_cache = {}

    def _precompute_move_dists(self):
        """Precompute movement distributions for all positions and move actions."""
        self.move_dist_table = {}
        for r in range(self.env.height):
            for c in range(self.env.width):
                if self.env.is_wall((r, c)): continue
                pos = (r, c)
                for action in [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT]:
                    self.move_dist_table[(pos, action)] = self._move_distribution(pos, action)

    def _precompute_redirt_probs(self):
        self.redirt_table: Dict[int, List[Tuple[float, int]]] = {}
        for mask in range(1 << self.num_dirt):
            outcomes = []
            clean_indices = [i for i in range(self.num_dirt) if not is_dirt_dirty(mask, i)]
            
            total_prob = 0.0
            for i in clean_indices:
                pos = self.env.dirt_positions[i]
                prob = self.config.P_REDIRT_CAT_ZONE if self.env.is_cat_influence(pos) else self.config.P_REDIRT_NORMAL
                outcomes.append((prob, set_dirt_dirty(mask, i)))
                total_prob += prob
                
            if total_prob > 1.0:
                outcomes = [(p / total_prob, m) for p, m in outcomes]
                p_nothing = 0.0
            else:
                p_nothing = 1.0 - total_prob
                
            if p_nothing > 1e-6: outcomes.append((p_nothing, mask))
            self.redirt_table[mask] = outcomes

    def get_actions(self, state: State) -> List[Action]:
        if self.is_terminal(state): return []
        
        # Optimization: use a fixed list
        battery = state[3]
        if battery > int(self.config.B_MAX * 0.95):
            return [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT, Action.CLEAN]
        return [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT, Action.CLEAN, Action.CHARGE]

    def _move_distribution(self, pos: Tuple[int, int], action: Action) -> List[Tuple[float, Tuple[int, int], str]]:
        dist: List[Tuple[float, Tuple[int, int], str]] = []
        is_wet = self.env.is_wet(pos)
        is_cat_center = self.env.is_cat_center(pos)
        is_cat_inf = self.env.is_cat_influence(pos)
        valid_adj = []
        for a in [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT]:
            np = get_next_pos(pos, a)
            if not self.env.is_wall(np): valid_adj.append(np)
        if not valid_adj: valid_adj.append(pos)
            
        def add_outcome(p: float, act: Action, evt: str):
            np = get_next_pos(pos, act)
            if self.env.is_wall(np):
                if self.env.is_cat_center(np):
                    dist.append((p, pos, "Cat interference (hit cat)."))
                else:
                    dist.append((p, pos, "Hit wall."))
            else: dist.append((p, np, evt))
                
        if is_cat_center or is_cat_inf:
            p_int = self.config.P_CAT_CENTER_INTENDED if is_cat_center else self.config.P_CAT_ZONE_INTENDED
            p_stay = self.config.P_CAT_CENTER_STAY if is_cat_center else self.config.P_CAT_ZONE_STAY
            p_push = self.config.P_CAT_CENTER_PUSH if is_cat_center else self.config.P_CAT_ZONE_PUSH
            add_outcome(p_int, action, "Moved as intended.")
            dist.append((p_stay, pos, "Cat interference (stay)."))
            pp = p_push / len(valid_adj)
            for np in valid_adj: dist.append((pp, np, "Cat interference (pushed)."))
        elif is_wet:
            add_outcome(self.config.P_WET_INTENDED, action, "Moved as intended on wet floor.")
            add_outcome(self.config.P_WET_SLIP, get_left_action(action), "Slipped left on wet floor.")
            add_outcome(self.config.P_WET_SLIP, get_right_action(action), "Slipped right on wet floor.")
        else:
            add_outcome(self.config.P_NORMAL_INTENDED, action, "Moved as intended.")
            add_outcome(self.config.P_NORMAL_SLIP, get_left_action(action), "Slipped left.")
            add_outcome(self.config.P_NORMAL_SLIP, get_right_action(action), "Slipped right.")
            
        collapsed: Dict[Tuple[Tuple[int, int], str], float] = {}
        for p, np, e in dist:
            key = (np, e); collapsed[key] = collapsed.get(key, 0.0) + p
        return [(p, np, e) for (np, e), p in collapsed.items() if p > 0]

    # These must be implemented by subclasses
    def get_all_states(self) -> List[State]: raise NotImplementedError
    def is_terminal(self, state: State) -> bool: raise NotImplementedError
    def get_transitions(self, state: State, action: Action) -> List[Tuple[float, State, float, str]]: raise NotImplementedError
    def compute_reward_internal(self, state: State, action: Action, next_pos: Tuple[int, int], next_mask: int, next_battery: int, event: str) -> float: raise NotImplementedError

    def compute_reward(self, state: State, action: Action, next_pos: Tuple[int, int], event: str) -> float:
        x, y, dirt_mask, battery = state
        pos = (x, y)
        next_mask = dirt_mask
        idx = self.env.get_dirt_index(pos)
        if action == Action.CLEAN and idx != -1 and is_dirt_dirty(dirt_mask, idx):
            next_mask = set_dirt_clean(dirt_mask, idx)
        next_battery = max(0, battery - (2 if action == Action.CLEAN and idx != -1 and is_dirt_dirty(dirt_mask, idx) else 1))
        if action == Action.CHARGE and pos == self.env.base_station: next_battery = self.config.B_MAX
        return self.compute_reward_internal(state, action, next_pos, next_mask, next_battery, event)
