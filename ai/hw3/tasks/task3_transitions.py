from typing import List, Tuple
from core.config import Action
from core.base_mdp import State
from core.utils import is_dirt_dirty, set_dirt_clean

from typing import List, Tuple
from core.base_mdp import State, Action
from core.utils import is_dirt_dirty, set_dirt_clean

def get_transitions(self, state: State, action: Action) -> List[Tuple[float, State, float, str]]:
    """
    [Task 3] 전이 확률(Transition Model) 구현
    주어진 상태에서 행동을 취했을 때 가능한 모든 다음 상태와 그 확률 반환.
    각 요소는 (확률, 다음 상태, 보상, 이벤트 설명) 튜플입니다.
    """
    # 1. Terminal state라면 빈 리스트 반환
    if self.is_terminal(state):
        return []

    x, y, dirt_mask, battery = state
    pos = (x, y)
    
    base_outcomes: List[Tuple[float, Tuple[int, int], int, int, str]] = []

    if action == Action.CHARGE:
        if pos == self.env.base_station:
            next_battery = self.config.B_MAX
            event = "Charged successfully."
        else:
            next_battery = max(0, battery - 1)
            event = "Invalid charge attempt."
        
        
        base_outcomes.append((1.0, pos, dirt_mask, next_battery, event))

    elif action == Action.CLEAN:
        idx = self.env.get_dirt_index(pos)
        
        if idx != -1 and is_dirt_dirty(dirt_mask, idx):
            next_mask = set_dirt_clean(dirt_mask, idx)
            next_battery = max(0, battery - 2)  
            event = "Cleaned dirt successfully."
        else:
            next_mask = dirt_mask
            next_battery = max(0, battery - 1)
            event = "Cleaned empty floor."
            
        base_outcomes.append((1.0, pos, next_mask, next_battery, event))

    else:
        move_dist = self.move_dist_table.get((pos, action), [(1.0, pos, "Stayed.")])
        next_battery = max(0, battery - 1)  
        
        for p_move, next_pos, move_event in move_dist:
            base_outcomes.append((p_move, next_pos, dirt_mask, next_battery, move_event))

    t_candidate = []
    
    for p_base, next_pos, intermediate_mask, next_battery, event in base_outcomes:
        if action == Action.CHARGE:
            reward = self.compute_reward(state, action, next_pos, event)
            final_state = (next_pos[0], next_pos[1], intermediate_mask, next_battery)
            t_candidate.append((p_base, final_state, reward, event))
            continue
            
        redirt_outcomes = self.redirt_table.get(intermediate_mask, [(1.0, intermediate_mask)])
        
        for p_redirt, final_mask in redirt_outcomes:
            combined_prob = p_base * p_redirt
            
            final_state = (next_pos[0], next_pos[1], final_mask, next_battery)
            
            reward = self.compute_reward(state, action, next_pos, event)
            
            t_candidate.append((combined_prob, final_state, reward, event))

    return t_candidate
