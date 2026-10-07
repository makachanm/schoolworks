# 과제 명세: 고양이가 있는 스마트홈 로봇청소기 MDP

## 1. 과제 목표

이번 과제에서는 확률적 격자 환경을 직접 MDP로 모델링하고, Dynamic Programming 계열 알고리즘으로 최적 정책을 구합니다.

학생은 다음 네 가지를 명확히 연결해야 합니다.

1. 상태가 무엇인지 정의한다.
2. 행동 이후 어떤 확률적 결과가 가능한지 전이 모델을 만든다.
3. 행동 결과에 대한 보상을 설계한다.
4. Value Iteration / Policy Iteration으로 최적 정책을 계산한다.

## 2. 구현 파일

학생 구현 파일은 아래 9개입니다.

- `tasks/task1_states.py`
- `tasks/task2_terminal.py`
- `tasks/task3_transitions.py`
- `tasks/task4_reward.py`
- `tasks/task5_value_iteration.py`
- `tasks/task6_policy_extraction.py`
- `tasks/task7_q_values.py`
- `tasks/task8_policy_evaluation.py`
- `tasks/task9_policy_iteration.py`

`core/`, `main_cli.py`, `main_web.py`, `templates/`는 읽어도 되지만 수정 대상이 아닙니다.
보고서는 `docs/01. report_template.docx`를 기본 템플릿으로 활용하십시오.

## 3. 권장 수행 순서

### 단계 A. MDP 모델부터 완성

- Task 1: 상태 공간 생성
- Task 2: 종료 조건 정의
- Task 3: 전이 확률 구현
- Task 4: 보상 함수 구현

이 단계가 끝나야 Bellman 업데이트에 필요한 `S`, `T`, `R`이 갖춰집니다.

### 단계 B. Value Iteration으로 정책 계산

- Task 5: Value Iteration
- Task 6: Policy Extraction

이 단계가 끝나면 `main_cli.py`와 `main_web.py`의 핵심 흐름이 동작합니다.

### 단계 C. Policy Iteration까지 확장

- Task 7: Q-value 계산
- Task 8: Policy Evaluation
- Task 9: Policy Iteration

이 단계가 끝나면 `tools/test_planners.py`로 두 알고리즘 결과를 비교할 수 있습니다.

## 4. Task 상세 안내

| Task | 파일 | 핵심 구현 내용 | 구현 후 확인 포인트 |
|---|---|---|---|
| 1 | `task1_states.py` | `(x, y, dirt_mask, battery)` 형태의 모든 유효 상태를 생성 | 벽을 제외한 모든 좌표가 포함되는지 확인 |
| 2 | `task2_terminal.py` | 배터리 소진 또는 목표 조건 달성 시 종료 처리 | `battery == 0`, `all clean + base` 조건 점검 |
| 3 | `task3_transitions.py` | 이동, 청소, 충전 행동에 대한 확률적 다음 상태 생성 | 확률 합이 1인지, redirt가 반영되는지 확인 |
| 4 | `task4_reward.py` | 이동 페널티, 벽 충돌, 고양이 간섭, 청소 성공, 충전 실패 등을 보상으로 설계 | 이벤트별 보상이 의도대로 분기되는지 확인 |
| 5 | `task5_value_iteration.py` | Bellman optimality update를 반복해 가치 함수 수렴 | `delta`가 감소하고 수렴 플래그가 설정되는지 확인 |
| 6 | `task6_policy_extraction.py` | 수렴한 가치 함수로부터 상태별 최적 행동 추출 | 비종료 상태마다 정책이 채워지는지 확인 |
| 7 | `task7_q_values.py` | `Q(s,a)` 기대값 계산 함수 작성 | 전이 확률과 다음 상태 가치가 함께 반영되는지 확인 |
| 8 | `task8_policy_evaluation.py` | 고정된 정책에 대한 `V^π(s)` 계산 | 정책이 주어졌을 때 값이 수렴하는지 확인 |
| 9 | `task9_policy_iteration.py` | 평가와 개선을 반복해 정책 안정화 | 안정화 이후 반복이 멈추는지 확인 |

## 5. 검증 흐름

### 6-1. 초기 점검

의존성을 준비합니다.

```bash
uv sync
```

### 6-2. Task 1~4 이후 권장 점검

상태 공간과 전이 함수를 가볍게 확인합니다.

```bash
uv run python -c "from core.environment import GridWorld; from core.student_wrapper import StudentMDP; env=GridWorld(); mdp=StudentMDP(env); print('base=', env.base_station, 'dirt=', len(env.dirt_positions)); print('num_states=', len(mdp.get_all_states()))"
```

```bash
uv run python -c "from core.environment import GridWorld; from core.student_wrapper import StudentMDP; from core.config import Action; env=GridWorld(); mdp=StudentMDP(env); s=(env.base_station[0], env.base_station[1], env.initial_dirt_mask, 100); print(mdp.get_transitions(s, Action.RIGHT)[:5])"
```

### 6-3. Task 5~6 이후 권장 점검

CLI와 웹 GUI가 실행 가능한지 확인합니다.

```bash
uv run python main_cli.py
```

```bash
uv run python main_web.py
```

`COMPUTE POLICY` 버튼은 `task5`와 `task6`이 끝나야 의미 있게 동작합니다.

### 6-4. Task 7~9 이후 최종 점검

```bash
uv run python tools/test_planners.py
```

```bash
uv run python tools/verify_performance.py
```

## 6. 구현 시 자주 놓치는 부분

- 상태 공간에서 벽 좌표를 포함하지 않는지 확인하세요.
- 청소 성공 시 배터리 소모량이 이동과 동일한지, 혹은 더 큰지 코드 흐름을 꼭 확인하세요.
- `CHARGE`는 충전소에서만 유효합니다.
- 확률적 이동과 재오염은 서로 다른 층의 확률 분기입니다.
- terminal state에서는 행동 목록과 정책 처리가 자연스럽게 비어야 합니다.

## 7. 생성형 AI 활용 원칙

- 생성형 AI 사용 자체는 금지하지 않지만, 사용한 부분과 검증 여부를 스스로 설명할 수 있어야 합니다.
- 상태 정의, 전이 모델, 보상 함수, Bellman update 같은 핵심 로직을 AI가 제안했다면 본인이 그 논리를 직접 이해하고 수정할 수 있어야 합니다.
- AI가 제안한 코드를 그대로 제출한 뒤 설명하지 못하는 경우 감점 또는 부정행위 판단의 대상이 될 수 있습니다.
- 가능하면 제출물 마지막에 `어떤 task에서 어떤 도움을 받았는지` 한두 줄로 남기십시오.
- AI를 사용하지 않았다면 `해당 없음`으로 명시하면 됩니다.

## 8. 보고서 작성 안내

- 제공된 `docs/01. report_template.docx`를 기반으로 작성하는 것을 권장합니다.
- 보고서에는 최소한 상태 정의, 전이 모델, 보상 설계, Value Iteration 결과, Policy Iteration 결과, 웹 GUI 또는 실행 결과 캡처, 생성형 AI 사용 내역이 포함되어야 합니다.
- 특히 `왜 그런 상태 표현을 선택했는지`, `왜 그런 보상 설계를 했는지`, `VI와 PI 결과를 어떻게 비교했는지`를 서술형으로 설명하는 것이 중요합니다.
- 최종 제출 시에는 가능하면 PDF로 변환하여 포함하십시오.

## 9. 제출 파일 형식 및 마감

- 마감일: 추후 LMS 또는 수업 공지 기준
- 권장 제출 파일명: `분반_학번_이름_AI과제4.zip`
- 특별한 추가 공지가 없다면 `보고서 PDF + tasks/ 폴더 전체`를 함께 압축해 제출하는 방식을 권장합니다.
- 생성형 AI를 사용했다면 사용 범위와 검증 여부를 제출 메모 또는 별도 파일에 함께 남기십시오.

권장 구조 예시:

```text
분반_학번_이름_AI과제4.zip
├── 분반_학번_이름_보고서.pdf
└── tasks/
    ├── task1_states.py
    ├── task2_terminal.py
    ├── task3_transitions.py
    ├── task4_reward.py
    ├── task5_value_iteration.py
    ├── task6_policy_extraction.py
    ├── task7_q_values.py
    ├── task8_policy_evaluation.py
    └── task9_policy_iteration.py
```

마감 시각이나 업로드 방식이 별도 공지와 다를 경우에는 반드시 최신 LMS 공지를 따르십시오.

## 10. 제출 전 체크리스트

- `tasks/` 내부 9개 파일의 `NotImplementedError`가 모두 제거되었는가
- CLI가 끝까지 실행되는가
- 웹 GUI에서 정책 계산과 step 진행이 가능한가
- `tools/test_planners.py`가 Value Iteration / Policy Iteration을 모두 수행하는가
- 생성형 AI를 사용했다면 사용 범위를 제출물에 명시했는가
- 제출 ZIP 파일명과 내부 구조가 공지 형식과 맞는가
