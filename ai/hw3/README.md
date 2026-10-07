# 2026학년도 1학기 인공지능 과제 4 패키지

이 패키지는 로봇청소기 MDP 과제를 위한 공통 구조를 제공합니다.  
`00_instructor_private/` 와 `01_student_release/` 는 같은 폴더 구조를 사용하며, 실질적인 차이는 `tasks/` 내부 구현 상태입니다.

## 빠른 시작

```bash
uv sync
uv run python main_cli.py
```

웹 GUI는 아래처럼 실행합니다.

```bash
uv run python main_web.py
```

브라우저에서 `http://127.0.0.1:5050` 을 열면 됩니다.

## 폴더 구조

- `core/`: 시뮬레이터 핵심 코드
- `tasks/`: 과제 구현 영역
- `templates/`: 웹 GUI 템플릿
- `docs/`: 안내문, 과제 명세, 보고서 템플릿, 스크린샷
- `tools/`: 검증 및 비교 실행 스크립트

## 먼저 읽을 파일

- `docs/00. instruction.html`
- `docs/assignment.md`
- `docs/01. report_template.docx`

## 자주 쓰는 실행 파일

- `main_cli.py`: CLI 시뮬레이션
- `main_web.py`: 웹 GUI 시뮬레이션
- `tools/test_planners.py`: Value Iteration / Policy Iteration 비교
- `tools/verify_performance.py`: 랜덤 맵 반복 검증

## 패키지 사용 메모

- student 배포본에서는 `tasks/task1_states.py` ~ `task9_policy_iteration.py`가 TODO 상태이며, 구현을 돕기 위한 주석이 들어 있습니다.
- instructor 검수본에서는 같은 파일 구조를 유지하면서 `tasks/` 내부가 참고 구현으로 채워져 있습니다.
- 제출 형식과 보고서 작성 기준은 `docs/00. instruction.html` 과 `docs/assignment.md` 를 기준으로 확인하십시오.
