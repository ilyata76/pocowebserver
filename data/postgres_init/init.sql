---
--
---

CREATE TABLE test1 (
    id integer NOT NULL,
    first_name varchar NOT NULL,
    last_name varchar NOT NULL,

    CONSTRAINT pk_test1_id PRIMARY KEY (id)
);

INSERT INTO test1
    VALUES
        (1, 'Abob', 'Abobov'),
        (2, 'Cringe', 'Cringenko'),
        (3, 'Ebob', 'Ebobko'),
        (4, 'DJ', 'Eban')
;

CREATE TABLE test2 (
    article_id integer PRIMARY KEY,
    article text NOT NULL,
    author_id integer NOT NULL,

    CONSTRAINT fk_test1_test2_id FOREIGN KEY (author_id) REFERENCES test1(id)
);

INSERT INTO test2
    VALUES
        (1, 'абобус в современном мире', 1),
        (2, 'абобус с точки зрения гендерной теории', 1),
        (3, 'диджей в политике', 4),
        (4, 'кринж как диспозиция сегодняшнего дня', 2)
;

-- poco=# SELECT * FROM test1, test2 WHERE test1.id=test2.author_id;
--  id | first_name | last_name | article_id |                article                 | author_id
-- ----+------------+-----------+------------+----------------------------------------+-----------
--   1 | Abob       | Abobov    |          1 | абобус в современном мире              |         1
--   1 | Abob       | Abobov    |          2 | абобус с точки зрения гендерной теории |         1
--   4 | DJ         | Eban      |          3 | диджей в политике                      |         4
--   2 | Cringe     | Cringenko |          4 | кринж как диспозиция сегодняшнего дня  |         2
-- (4 rows)