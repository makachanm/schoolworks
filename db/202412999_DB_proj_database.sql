CREATE TABLE `paper` (
	`id`	int	NOT NULL,
	`author_id`	int	NOT NULL,
	`genre`	VARCHAR(255)	NULL,
	`title`	VARCHAR(255)	NULL,
	`submission_date`	DATETIME	NULL
);

CREATE TABLE `author` (
	`id`	int	NOT NULL,
	`name`	VARCHAR(255)	NULL,
	`contact`	VARCHAR(255)	NULL,
	`joined`	TINYINT(1)	NULL,
	`org`	VARCHAR(255)	NULL
);

CREATE TABLE `review` (
	`reviewer_id`	int	NOT NULL,
	`paper_id`	int	NOT NULL,
	`author_id`	int	NOT NULL,
	`content`	TEXT	NULL,
	`passed`	TINYINT(1)	NULL
);

CREATE TABLE `reviewer` (
	`id`	int	NOT NULL,
	`name`	VARCHAR(255)	NULL,
	`contact`	VARCHAR(255)	NULL,
	`major`	VARCHAR(255)	NULL,
	`org`	VARCHAR(255)	NULL
);

CREATE TABLE `sessions` (
	`id`	int	NOT NULL,
	`id2`	int	NOT NULL,
	`author_id`	int	NOT NULL,
	`place`	VARCHAR(255)	NULL,
	`time`	DATETIME	NULL
);

ALTER TABLE `paper` ADD CONSTRAINT `PK_PAPER` PRIMARY KEY (
	`id`,
	`author_id`
);

ALTER TABLE `author` ADD CONSTRAINT `PK_AUTHOR` PRIMARY KEY (
	`id`
);

ALTER TABLE `review` ADD CONSTRAINT `PK_REVIEW` PRIMARY KEY (
	`reviewer_id`,
	`paper_id`,
	`author_id`
);

ALTER TABLE `reviewer` ADD CONSTRAINT `PK_REVIEWER` PRIMARY KEY (
	`id`
);

ALTER TABLE `sessions` ADD CONSTRAINT `PK_SESSIONS` PRIMARY KEY (
	`id`,
	`id2`,
	`author_id`
);

ALTER TABLE `paper` ADD CONSTRAINT `FK_author_TO_paper_1` FOREIGN KEY (
	`author_id`
)
REFERENCES `author` (
	`id`
);

ALTER TABLE `review` ADD CONSTRAINT `FK_reviewer_TO_review_1` FOREIGN KEY (
	`reviewer_id`
)
REFERENCES `reviewer` (
	`id`
);

ALTER TABLE `review` ADD CONSTRAINT `FK_paper_TO_review_1` FOREIGN KEY (
	`paper_id`
)
REFERENCES `paper` (
	`id`
);

ALTER TABLE `review` ADD CONSTRAINT `FK_paper_TO_review_2` FOREIGN KEY (
	`author_id`
)
REFERENCES `paper` (
	`author_id`
);

ALTER TABLE `sessions` ADD CONSTRAINT `FK_paper_TO_sessions_1` FOREIGN KEY (
	`id2`
)
REFERENCES `paper` (
	`id`
);

ALTER TABLE `sessions` ADD CONSTRAINT `FK_paper_TO_sessions_2` FOREIGN KEY (
	`author_id`
)
REFERENCES `paper` (
	`author_id`
);

INSERT INTO `author` (`id`, `name`, `contact`, `joined`, `org`) VALUES
(1, '김철수', 'chulsoo@univ.ac.kr', 1, '한국대학교'),
(2, '이영희', 'younghee@lab.res.kr', 1, '미래연구소'),
(3, '박민준', 'minjun@tech.com', 0, '혁신테크');

INSERT INTO `reviewer` (`id`, `name`, `contact`, `major`, `org`) VALUES
(101, '최박사', 'choi@univ.ac.kr', '컴퓨터공학', '한국대학교'),
(102, '정교수', 'jung@science.ac.kr', '데이터베이스', '대한대학교'),
(103, 'Hong', 'hong@global.edu', '인공지능', '글로벌대학');

INSERT INTO `paper` (`id`, `author_id`, `genre`, `title`, `submission_date`) VALUES
(10, 1, 'Database', '정규화 이론의 실무 적용 연구', '2026-05-10 14:00:00'),
(20, 2, 'AI', '거대 언어 모델의 경량화 기법', '2026-05-12 09:30:00'),
(30, 3, 'Security', '블록체인 기반 인증 시스템 설계', '2026-05-15 18:20:00'),
(10, 2, 'Database', '분산 데이터베이스 환경에서의 동기화', '2026-05-16 11:00:00'); 

INSERT INTO `review` (`reviewer_id`, `paper_id`, `author_id`, `content`, `passed`) VALUES
(101, 10, 1, '주제가 신선하고 정규화 분석이 치밀합니다.', 1),
(102, 10, 1, '실무 데이터셋에 대한 실험이 추가되면 좋겠습니다.', 1),
(102, 20, 2, '실험 결과의 신뢰성이 높고 짜임새가 있습니다.', 1),
(103, 30, 3, '기존 연구와의 차별성이 다소 부족합니다.', 0);

INSERT INTO `sessions` (`id`, `id2`, `author_id`, `place`, `time`) VALUES
(1001, 10, 1, '제1컨퍼런스룸 301호', '2026-06-20 10:00:00'),
(1001, 20, 2, '제1컨퍼런스룸 301호', '2026-06-20 11:00:00'),
(1002, 10, 2, '오디토리움 B', '2026-06-21 14:00:00');
