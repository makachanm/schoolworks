import time
from core.config import Action

def run_value_iteration(self) -> None:
    """
    [Task 5] Value Iteration 알고리즘 구현
    벨만 최적 방정식(Bellman Optimality Equation)을 사용하여 상태 가치(Value Function)가 수렴할 때까지 반복(Iteration)합니다.

    구현 체크포인트:
    1. self.states, self.state_to_idx, self.values_list 초기화
    2. 각 iteration마다 모든 비종료 상태 업데이트
    3. 각 상태에서 max_a Q(s, a) 계산
    4. delta 기록 후 THETA보다 작으면 수렴 처리
    5. iterations, delta_history, compute_time, converged 관리

    HINT:
    - In-place (Gauss-Seidel) 업데이트 권장
    - Task 7의 compute_q_value를 재사용하면 구조가 깔끔합니다.
    """
    start_time = time.time()
    
    self.states = self.mdp.get_all_states()
    self.state_to_idx = {state: i for i, state in enumerate(self.states)}
    self.values_list = [0.0] * len(self.states)
    
    self.iterations = 0
    self.delta_history = []
    self.converged = False
    
    theta = self.config.THETA
    max_iterations = self.config.MAX_ITERATIONS
    actions = [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT, Action.CLEAN, Action.CHARGE]

    while self.iterations < max_iterations:
        delta = 0.0
        
        for state in self.states:
            if self.mdp.is_terminal(state):
                continue
                
            state_idx = self.state_to_idx[state]
            old_value = self.values_list[state_idx]
            
            max_q = float('-inf')
            for action in actions:
                q_value = self.compute_q_value(state, action, self.values_list)
                if q_value > max_q:
                    max_q = q_value
            
            self.values_list[state_idx] = max_q
            delta = max(delta, abs(old_value - max_q))
            
        self.iterations += 1
        self.delta_history.append(delta)
        
        if delta < theta:
            self.converged = True
            break

    self.compute_time = time.time() - start_time
