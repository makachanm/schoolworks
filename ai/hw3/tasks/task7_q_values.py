from typing import List
from core.config import Action
from core.base_mdp import State

def compute_q_value(self, state: State, action: Action, values: List[float]) -> float:
    """
    [Task 7] Q-Value 계산
    특정 상태(state)에서 특정 행동(action)을 취했을 때의 기대 가치 Q(s, a)를 계산합니다.
    Q(s, a) = sum_{s'} T(s, a, s') * [R(s, a, s') + gamma * V(s')]

    구현 순서:
    1. self.mdp.get_transitions(state, action) 호출
    2. 각 next_state의 index를 self.state_to_idx 에서 찾기
    3. 확률 * (보상 + gamma * 다음 상태 가치) 누적
    """
    q_value = 0.0
    gamma = self.config.GAMMA
    transitions = self.mdp.get_transitions(state, action)

    for prob, next_state, reward, event in transitions:
        next_idx = self.state_to_idx[next_state]        
        next_value = values[next_idx]
        
        q_value += prob * (reward + gamma * next_value)

    return q_value
