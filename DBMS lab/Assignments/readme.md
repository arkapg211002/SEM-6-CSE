#### NOTES
```sql
-- GET A LIST OF TABLES CREATED IN THE LAST N DAYS
SELECT OBJECT_NAME, CREATED
FROM DBA_OBJECTS
WHERE OBJECT_TYPE = 'TABLE'
AND CREATED >= SYSDATE - 5;

```
```sql
-- IF DROP NOT POSSIBLE GET THE CONSTRAINT NAME AND ALTER THE CHILD TABLE
SELECT CONSTRAINT_NAME FROM USER_CONSTRAINTS
WHERE TABLE_NAME = <table with foreign key> AND (R_CONSTRAINT_NAME IN
(SELECT CONSTRAINT_NAME FROM USER_CONSTRAINTS WHERE TABLE_NAME = <table with primary key>));

ALTER TABLE <table with foreign key> DROP CONSTRAINT <constraint_name>;
-- THEN DROP
DROP TABLE <table with primary key>;
```
```SQL
-- TO CONVERT ANY STRING DATE TO TYPE DATE
SELECT TO_DATE('2024-03-17', 'YYYY-MM-DD') AS converted_date
FROM dual;
```
```SQL
-- TO ROUND DATES
SELECT ROUND(TO_DATE('1-4-1','DD-MM-YYYY'),'YEAR') FROM DUAL;
```
```SQL
-- CHECK CONSTRAINT 
-- Query to check details of constraints on the EMPLOYEE table
SELECT constraint_name, constraint_type, search_condition
FROM all_constraints
WHERE table_name = '<TABLE NAME>';

-- Query to check details of a specific constraint on the EMPLOYEE table
SELECT constraint_name, constraint_type, search_condition, r_constraint_name, delete_rule
FROM all_constraints
WHERE table_name = '<TABLE NAME>' AND constraint_name = '<CONSTRAINT NAME>';
```
