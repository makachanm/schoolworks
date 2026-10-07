from typing import Dict, List
from core.config import Action
from core.base_mdp import State

def run_policy_evaluation(self, policy_dict: Dict[State, Action]) -> List[float]:
    """
    [Task 8] Policy Evaluation 구현
    주어진 정책(policy_dict)에 대해 상태 가치 함수 V^pi(s)를 계산합니다.

    구현 체크포인트:
    - terminal state는 업데이트하지 않음
    - 각 상태는 policy_dict[state]가 지정한 행동 하나만 사용
    - delta < THETA 가 될 때까지 반복

    HINT: Gauss-Seidel iteration을 사용하면 Value Iteration과 비슷한 구조로 작성할 수 있습니다.
    """
    theta = self.config.THETA
    max_iterations = self.config.MAX_ITERATIONS
    
    while True:
        delta = 0.0
        
        for state in self.states:
            if self.mdp.is_terminal(state):
                continue
                
            state_idx = self.state_to_idx[state]
            old_value = self.values_list[state_idx]
            
            action = policy_dict.get(state)
            if action is None:
                continue
                
            new_value = self.compute_q_value(state, action, self.values_list)
            
            self.values_list[state_idx] = new_value
            delta = max(delta, abs(old_value - new_value))
            
        if delta < theta:
            break
            
    return self.values_list

