from core.base_mdp import State

def is_terminal(self, state: State) -> bool:
    """
    [Task 2] 종료 조건 정의
    로봇이 언제 멈춰야 하는지 결정합니다.
    
    체크포인트:
    - 배터리(battery)가 0이면 종료
    - 모든 먼지(dirt_mask == 0)를 청소했고
    - 로봇 위치가 self.env.goal_pos 와 같으면 종료

    즉, "먼지를 다 청소하고 충전소로 복귀"해야 성공 종료입니다.
    """
    x, y, dirt_mask, battery = state
    
    # Condition 1: Battery dead
    if battery <= 0:
        return True
    
    # Condition 2: All dirt cleaned AND at goal position
    if dirt_mask == 0 and (x, y) == self.env.goal_pos:
        return True
        
    return False
