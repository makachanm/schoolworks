import random
from typing import Tuple, List, Optional
from core.config import Config, Action
from core.utils import is_dirt_dirty, set_dirt_dirty

State = Tuple[int, int, int, int]

class Simulator:
    def __init__(self, mdp):
        self.mdp = mdp
        self.config = Config()
        self.reset()

    def reset(self) -> State:
        self.current_state: State = (
            self.mdp.env.base_station[0],
            self.mdp.env.base_station[1],
            self.mdp.env.initial_dirt_mask,
            self.config.B_MAX
        )
        self.total_reward: float = 0.0
        self.steps: int = 0
        return self.current_state

    def step(self, action: Action) -> Tuple[State, float, bool, str]:
        if self.mdp.is_terminal(self.current_state):
            return self.current_state, 0.0, True, "Already at terminal state."

        transitions = self.mdp.get_transitions(self.current_state, action)
        if not transitions:
            return self.current_state, 0.0, False, "No valid transitions found."

        probs = [t[0] for t in transitions]
        r = random.random()
        cumulative_p = 0.0
        selected_transition = transitions[-1]
        for t in transitions:
            cumulative_p += t[0]
            if r <= cumulative_p:
                selected_transition = t
                break

        prob, next_state, reward, event = selected_transition
        next_state = self._apply_stochastic_redirt(next_state)

        self.current_state = next_state
        self.total_reward += reward
        self.steps += 1
        is_done = self.mdp.is_terminal(self.current_state)
        return next_state, reward, is_done, event

    def _apply_stochastic_redirt(self, state: State) -> State:
        x, y, mask, battery = state
        new_mask = mask
        for i, pos in enumerate(self.mdp.env.dirt_positions):
            if not is_dirt_dirty(mask, i):
                base_prob = self.config.P_REDIRT_CAT_ZONE if self.mdp.env.is_cat_influence(pos) else self.config.P_REDIRT_NORMAL
                # Decay the probability as steps increase to simulate the cat getting tired
                prob = base_prob * (0.95 ** self.steps)
                if random.random() < prob:
                    new_mask = set_dirt_dirty(new_mask, i)
        return (x, y, new_mask, battery)
