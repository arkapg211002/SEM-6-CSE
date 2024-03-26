/*

Consider the following tables:
MATCH (match_id, team1, team2, ground, mdate, winner)
PLAYER (p_id, lname, fname, country, yborn, bplace, ftest)
BATTING (match_id, p_id, mts, order, out_type, fow, nruns, nballs, fours, sixes)
BOWLING (match_id, p_id, novers, maidens, nruns, nwickets)

*/

CREATE TABLE MATCH(
	MATCH_ID VARCHAR2(10) PRIMARY KEY,
	TEAM1 VARCHAR2(20) NOT NULL,
	TEAM2 VARCHAR2(20) NOT NULL,
	GROUND VARCHAR2(20),
	MDATE DATE,
	WINNER NUMBER CONSTRAINT M1 CHECK(WINNER IN (1,2))
);

CREATE TABLE PLAYER (
	P_ID VARCHAR2(10) PRIMARY KEY,
	LNAME VARCHAR2(20),
	FNAME VARCHAR2(20),
	COUNTRY VARCHAR2(20),
	YBORN NUMBER,
	BPLACE VARCHAR2(20),
	FTEST NUMBER
);

CREATE TABLE BATTING (
	MATCH_ID VARCHAR2(10),
	P_ID VARCHAR2(10),
	MTS NUMBER,
	BATTING_ORDER NUMBER,
	OUT_TYPE VARCHAR2(20),
	FOW VARCHAR2(20),
	NRUNS NUMBER,
	NBALLS NUMBER,
	FOURS NUMBER,
	SIXES NUMBER,
	CONSTRAINT BFK1 FOREIGN KEY (P_ID) REFERENCES PLAYER(P_ID) ON DELETE CASCADE,
	CONSTRAINT BFK2 FOREIGN KEY (MATCH_ID) REFERENCES MATCH(MATCH_ID) ON DELETE CASCADE
);

CREATE TABLE BOWLING (
	MATCH_ID VARCHAR2(10),
	P_ID VARCHAR2(10),
	NOVERS NUMBER,
	MAIDENS NUMBER,
	NRUNS NUMBER,
	NWICKETS NUMBER,
	CONSTRAINT BWFK1 FOREIGN KEY (MATCH_ID) REFERENCES MATCH(MATCH_ID) ON DELETE CASCADE,
	CONSTRAINT BWFK2 FOREIGN KEY (P_ID) REFERENCES PLAYER(P_ID) ON DELETE CASCADE
);

-- Sample data for MATCH table
INSERT ALL 
    INTO MATCH VALUES ('M1', 'Australia', 'India', 'Sydney', TO_DATE('01-01-2023', 'DD-MM-YYYY'), 1)
    INTO MATCH VALUES ('M2', 'India', 'Australia', 'Sydney', TO_DATE('05-01-2023', 'DD-MM-YYYY'), 2)
    INTO MATCH VALUES ('M3', 'Australia', 'England', 'Melbourne', TO_DATE('10-01-2023', 'DD-MM-YYYY'), 1)
    INTO MATCH VALUES ('M4', 'England', 'Australia', 'Sydney', TO_DATE('15-01-2023', 'DD-MM-YYYY'), 2)
    INTO MATCH VALUES ('M5', 'Australia', 'India', 'Sydney', TO_DATE('20-01-2023', 'DD-MM-YYYY'), 1)
SELECT * FROM DUAL;

-- Sample data for PLAYER table
INSERT ALL 
    INTO PLAYER VALUES ('27001', 'Smith', 'Steven', 'Australia', 1988, 'Sydney', 40)
    INTO PLAYER VALUES ('27002', 'Kohli', 'Virat', 'India', 1988, 'Delhi', 55)
    INTO PLAYER VALUES ('27003', 'Root', 'Joe', 'England', 1990, 'Sheffield', 50)
    INTO PLAYER VALUES ('27004', 'Warner', 'David', 'Australia', 1986, 'Sydney', 45)
    INTO PLAYER VALUES ('27005', 'Stokes', 'Ben', 'England', 1991, 'London', 60)
SELECT * FROM DUAL;

-- Sample data for BATTING table
INSERT ALL 
    INTO BATTING VALUES ('M1', '27001', 1, 1, 'Not out', NULL, 80, 100, 8, 1)
    INTO BATTING VALUES ('M1', '27002', 1, 2, 'Caught', '20/1', 30, 40, 4, 0)
    INTO BATTING VALUES ('M2', '27003', 1, 3, 'LBW', '30/2', 25, 35, 3, 0)
    INTO BATTING VALUES ('M2', '27004', 1, 4, 'Not out', NULL, 90, 110, 10, 2)
    INTO BATTING VALUES ('M3', '27005', 1, 5, 'Run out', '50/3', 45, 55, 6, 0)
SELECT * FROM DUAL;

-- Sample data for BOWLING table
INSERT ALL 
    INTO BOWLING VALUES ('M1', '27001', 10, 2, 60, 2)
    INTO BOWLING VALUES ('M1', '27002', 8, 1, 45, 1)
    INTO BOWLING VALUES ('M2', '27003', 9, 0, 55, 1)
    INTO BOWLING VALUES ('M2', '27004', 10, 3, 40, 2)
    INTO BOWLING VALUES ('M3', '27005', 9, 1, 65, 0)
SELECT * FROM DUAL;

-- i)Find match ids of those matches in which player 27001 bats and makes more runs than he made at every match he played at Sydney.
SELECT DISTINCT b.MATCH_ID
FROM BATTING B
WHERE B.P_ID = '27001'
AND B.NRUNS > ALL (
    SELECT B2.NRUNS
    FROM BATTING B2
    JOIN MATCH M ON B2.MATCH_ID = M.MATCH_ID
    WHERE B2.P_ID = '27001'
    AND M.GROUND = 'Sydney'
);


-- ii)Find player ids of players who have scored more than 30 in every ODI match that they have batted.
SELECT B.P_ID 
FROM BATTING B
JOIN MATCH M ON M.MATCH_ID = B.MATCH_ID
WHERE B.NRUNS > 30;

-- iii)Find the ids of players that had a higher average score than the average score for all players when they played in Sri Lanka.
CREATE TABLE AVGRUNS AS SELECT AVG(NRUNS) AS AVGR , P_ID FROM BATTING GROUP BY P_ID;
SELECT P_ID 
FROM AVGRUNS 
WHERE AVGR > (SELECT AVG(NRUNS) 
			  FROM BATTING B 
			  JOIN MATCH M ON M.MATCH_ID = B.MATCH_ID 
			  WHERE M.GROUND = 'Srilanka');