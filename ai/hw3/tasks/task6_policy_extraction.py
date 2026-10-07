from core.config import Action

def extract_policy(self) -> None:
    """
    [Task 6] Policy Extraction 구현
    최종 수렴한 가치 함수 V*(s)를 바탕으로 각 상태에서 취해야 할 최적의 행동 π*(s)를 도출해 self.policy_dict에 저장합니다.

    구현 체크포인트:
    - terminal state는 정책에서 제외
    - 가능한 action들 중 Q(s, a)가 최대인 행동 선택
    - 결과를 self.policy_dict[state] = best_action 형태로 저장

    HINT: Task 7의 compute_q_value를 그대로 호출하면 됩니다.
    """
    self.policy_dict = {}
    actions = [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT, Action.CLEAN, Action.CHARGE]

    for state in self.states:
        if self.mdp.is_terminal(state):
            continue

        best_action = None
        max_q = float('-inf')

        for action in actions:
            q_value = self.compute_q_value(state, action, self.values_list)
            if q_value > max_q:
                max_q = q_value
                best_action = action

        if best_action is not None:
            self.policy_dict[state] = best_action

