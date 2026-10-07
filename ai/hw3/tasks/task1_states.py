from typing import List
from core.base_mdp import State

def get_all_states(self) -> List[State]:
    """
    [Task 1] 상태 공간(State Space) 생성
    Return a list of all possible valid states in the environment.

    State tuple structure:
    - (x, y, dirt_mask, battery)

    구현 체크포인트:
    1. (x, y)는 벽이 아닌 좌표만 포함합니다.
    2. dirt_mask는 0부터 (1 << num_dirt) - 1 까지 모두 고려합니다.
    3. battery는 0부터 B_MAX까지의 모든 값을 고려합니다.
    4. Value Iteration 수렴 속도를 위해 battery 오름차순 순회가 유리합니다.
    """

    states = []
    
    valid_positions = []
    for r in range(self.env.height):
        for c in range(self.env.width):
            if not self.env.is_wall((r, c)):
                valid_positions.append((r, c))
                
    num_dirt_states = 1 << self.num_dirt
    b_max = self.config.B_MAX
    
    for battery in range(b_max + 1):
        for (r, c) in valid_positions:
            for dirt_mask in range(num_dirt_states):
                states.append((r, c, dirt_mask, battery))

    return states