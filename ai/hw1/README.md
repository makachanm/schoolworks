# AI Assignment 1: 8-Puzzle Search Lab

이 저장소는 인공지능 과제 1(8-Puzzle 탐색 알고리즘 구현/실험/분석)을 위한 통합 프로젝트입니다.

## 폴더 구조

```text
.
├─ 01_student_release/     # 학생 배포용 자료
└─ 00_instructor_private/  # 교수자 전용 자료(배포 금지)
```

## 학생용 (`01_student_release`)

주요 파일:
- `search.py`: 학생이 구현해서 ZIP에 포함해 제출할 파일
- `eightpuzzle.py`: 퍼즐 상태/이동 규칙 정의
- `main.py`: 콘솔 실행
- `main_ui.py`: 브라우저 UI 실행
- `00. instruction.html`: 브라우저용 과제 안내문
- `00. instruction.pdf`: 배포용 PDF 안내문
- `01. report_template.docx`: 보고서 템플릿

실행 예시:

```bash
cd 01_student_release
python3 main.py
# 또는
python3 main_ui.py
```

UI 주소:
- `http://127.0.0.1:8000`

학생 코드 수정 규칙:
- 학생은 `search.py`만 수정해야합니다.
- `eightpuzzle.py`, `main.py`, `main_ui.py`, 안내문/템플릿 파일은 수정하지 않습니다.

학생 제출 방식:
- 제출은 ZIP 파일 1개로 진행해야합니다.
- ZIP 내부에는 `search.py`와 보고서 PDF가 모두 포함되어야합니다.

## 교강사용 (`00_instructor_private`)

주요 파일/폴더:
- `search_solution.py`: 정답 구현
- `reference_code/`: 검증용 전체 기준 코드
- `autograder/grade_submissions.py`: 자동 채점 스크립트
- `autograder/submissions/`: 학생 제출 ZIP 보관 폴더
- `autograder/results/`: 채점 결과 CSV 출력 폴더

자동 채점:

```bash
python3 00_instructor_private/autograder/grade_submissions.py
```

옵션 예시:

```bash
python3 00_instructor_private/autograder/grade_submissions.py \
  --submissions-dir 00_instructor_private/autograder/submissions \
  --output 00_instructor_private/autograder/results/grades.csv
```

## 주의

- `00_instructor_private` 폴더는 학생에게 배포하지 않습니다.
- 과제 안내/제출 기준은 `01_student_release/00. instruction.html`을 기준으로 관리해야합니다.
