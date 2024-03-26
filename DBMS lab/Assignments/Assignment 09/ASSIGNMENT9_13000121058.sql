/*

Create the tables and insert 5 sets of records into each. 
employee (personname, street, city) 
works (personname, companyname, salary) 
company (companyname, city) 
manages (personname, managername) 

*/

-- EXISTING TABLE EMPLOYEE RENAMED TO EMPLOYEE1
-- RENAME EMPLOYEE TO EMPLOYEE1;

CREATE TABLE EMPLOYEE(
	PERSONNAME VARCHAR2(20) PRIMARY KEY,
	STREET VARCHAR2(20),
	CITY VARCHAR2(20)
);

-- RENAME WORKS TO WORKS1;

CREATE TABLE WORKS(
	PERSONNAME VARCHAR2(20),
	COMPANYNAME VARCHAR2(20),
	SALARY NUMBER,
	CONSTRAINT WFK1 FOREIGN KEY (PERSONNAME) REFERENCES EMPLOYEE(PERSONNAME) ON DELETE CASCADE,	
	CONSTRAINT WFK2 FOREIGN KEY (COMPANYNAME) REFERENCES COMPANY(COMPANYNAME) ON DELETE CASCADE
);

-- RENAME COMPANY TO COMPANY1;

CREATE TABLE COMPANY(
	COMPANYNAME VARCHAR2(20) PRIMARY KEY,
	CITY VARCHAR2(20)
);

CREATE TABLE MANAGES(
	PERSONNAME VARCHAR2(20),
	MANAGERNAME VARCHAR2(20),
	CONSTRAINT MFK1 FOREIGN KEY (PERSONNAME) REFERENCES EMPLOYEE(PERSONNAME) ON DELETE CASCADE
);

-- INSERT INTO TABLES

INSERT ALL
    INTO EMPLOYEE VALUES ('ARKA', '123 Main St', 'New York')
    INTO EMPLOYEE VALUES ('JOHN', '456 Elm St', 'Los Angeles')
    INTO EMPLOYEE VALUES ('MOHIT', '789 Oak St', 'Chicago')
    INTO EMPLOYEE VALUES ('ABC', '999 Maple St', 'Houston')
    INTO EMPLOYEE VALUES ('XYZ', '111 Pine St', 'San Francisco')
SELECT * FROM DUAL;

INSERT ALL
    INTO WORKS VALUES ('ARKA', 'Google', 100000)
    INTO WORKS VALUES ('JOHN', 'Microsoft', 150000)
    INTO WORKS VALUES ('MOHIT', 'Amazon', 250000)
    INTO WORKS VALUES ('XYZ', 'Axis Bank', 200000)
    INTO WORKS VALUES ('ABC', 'Axis Bank', 280000)
SELECT * FROM DUAL;

INSERT ALL
    INTO COMPANY VALUES ('Google', 'Mountain View')
    INTO COMPANY VALUES ('Microsoft', 'Redmond')
    INTO COMPANY VALUES ('Amazon', 'Seattle')
    INTO COMPANY VALUES ('Axis Bank', 'Mumbai')
    INTO COMPANY VALUES ('Walmart', 'Bentonville')
SELECT * FROM DUAL;

INSERT ALL
    INTO MANAGES VALUES ('JOHN', 'ARKA')
    INTO MANAGES VALUES ('MOHIT', 'ARKA')
    INTO MANAGES VALUES ('ABC', 'MOHIT')
    INTO MANAGES VALUES ('XYZ', 'JOHN')
    INTO MANAGES VALUES ('ABC', 'JOHN')
SELECT * FROM DUAL;

-- a)Find the names of all employees who work for Axis Bank. 
SELECT PERSONNAME FROM WORKS WHERE COMPANYNAME = 'AXIS BANK';

-- b)Find the names and cities of residence of all employees who work for Axis Bank.
SELECT E.PERSONNAME , E.CITY 
FROM EMPLOYEE E
JOIN WORKS W ON W.PERSONNAME = E.PERSONNAME
WHERE W.COMPANYNAME = 'Axis Bank';

-- c)Find the names, street addresses, and cities of residence of all employees who work for Axis Bank and earn more than Rs.30000 per annum. 
SELECT E.PERSONNAME , E.STREET , E.CITY 
FROM EMPLOYEE E 
JOIN WORKS W ON W.PERSONNAME = E.PERSONNAME 
WHERE W.COMPANYNAME = 'Axis Bank' AND W.SALARY > 30000;

-- d)Find all employees who live in the same city as the company for which they work is located.
SELECT E.PERSONNAME
FROM EMPLOYEE E
JOIN WORKS W ON W.PERSONNAME = E.PERSONNAME
JOIN COMPANY C ON W.COMPANYNAME = C.COMPANYNAME 
WHERE C.CITY = E.CITY;

-- e)Find all employees who live in the same city and on the same street as their managers.
SELECT E.PERSONNAME FROM EMPLOYEE E
WHERE E.CITY IN (SELECT CITY FROM EMPLOYEE WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES))
AND E.STREET IN (SELECT STREET FROM EMPLOYEE WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES))
AND E.PERSONNAME NOT IN (SELECT DISTINCT MANAGERNAME FROM MANAGES);

-- f)Find all employees in the database who do not work for Axis Bank.
SELECT E.PERSONNAME 
FROM EMPLOYEE E
JOIN WORKS W ON E.PERSONNAME = W.PERSONNAME
WHERE W.COMPANYNAME <> 'Axis Bank';

-- g)Find all employees who earn more than every employee of Axis Bank. 
SELECT PERSONNAME FROM WORKS WHERE SALARY > (SELECT MAX(SALARY) FROM WORKS WHERE COMPANYNAME = 'Axis Bank');

-- h)Assume that the companies may be located in several cities. Find all companies located in every city in which Axis Bank is located.
SELECT DISTINCT COMPANYNAME FROM COMPANY WHERE CITY IN (SELECT CITY FROM COMPANY WHERE COMPANYNAME = 'Axis Bank') AND COMPANYNAME <> 'Axis Bank';

-- i)Find all employees who earn more than the average salary of all employees of their company
CREATE TABLE TMPSAL AS SELECT AVG(SALARY) AS AVGSAL , COMPANYNAME FROM WORKS GROUP BY COMPANYNAME;

SELECT W.PERSONNAME , W.COMPANYNAME , W.SALARY 
FROM WORKS W
JOIN TMPSAL T ON W.COMPANYNAME = T.COMPANYNAME
WHERE W.SALARY > T.AVGSAL;

-- j)Find the company that has the most employees.
SELECT COMPANYNAME FROM (SELECT COUNT(PERSONNAME) AS TOT, COMPANYNAME FROM WORKS GROUP BY COMPANYNAME ORDER BY TOT DESC) WHERE ROWNUM = 1; 

-- k)Find the company that has the smallest payroll. 

SELECT COMPANYNAME FROM (SELECT SUM(SALARY) AS PAYROLL , COMPANYNAME FROM WORKS GROUP BY COMPANYNAME ORDER BY PAYROLL ASC) WHERE ROWNUM = 1;

-- l)Find those companies whose employees earn a higher salary, on average, than the average salary at Axis Bank.
SELECT COMPANYNAME FROM TMPSAL WHERE AVGSAL > (SELECT AVGSAL FROM TMPSAL WHERE COMPANYNAME = 'Axis Bank');

-- m)Modify the database so that ABC now lives in Kolkata. 
UPDATE EMPLOYEE SET CITY = 'Kolkata' WHERE PERSONNAME = 'ABC';

-- n)Give all employees of Axis Bank a 10 percent raise. 
UPDATE WORKS SET SALARY = SALARY * 1.10 WHERE COMPANYNAME = 'Axis Bank';

-- o)Give all managers in the database a 10 percent raise.
UPDATE WORKS SET SALARY = SALARY * 1.1 WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES);

/* 
P) Give all managers in the database a 10 percent raise, unless the salary would be greater than Rs.300000. In such cases, give only a 3 percent raise. 

READ : https://oracle-base.com/articles/9i/case-expressions-and-statements-9i#:~:text=The%20searched%20CASE%20expression%20is%20also%20supported%20in%20PL%2FSQL.&text=sal_desc)%3B%20END%3B%20%2F-,All%20possible%20values%20returned%20by%20a%20CASE%20expression,of%20the%20same%20data%20type.
*/
UPDATE WORKS SET SALARY = 
CASE
	WHEN SALARY*1.1 <= 300000 THEN SALARY*1.1
	ELSE SALARY*1.03
END
WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES);

-- q) Delete all tuples in the works relation for employees of Axis Bank. 
DELETE FROM WORKS WHERE COMPANYNAME = 'Axis Bank';