-- Create Cinema table
CREATE TABLE CINEMA (
    CID NUMBER PRIMARY KEY,
    CNAME VARCHAR2(100),
    CITY VARCHAR2(100),
    OWNER_NAME VARCHAR2(100)
);

-- Insert sample data into Cinema
INSERT ALL 
INTO CINEMA VALUES (1, 'Cineplex', 'Mumbai', 'John Doe')
INTO CINEMA VALUES (2, 'Regal Cinema', 'Delhi', 'Jane Smith')
INTO CINEMA VALUES (3, 'PVR', 'Mumbai', 'Alice Johnson')
INTO CINEMA VALUES (4, 'Inox', 'Rajkot', 'David Brown')
INTO CINEMA VALUES (5, 'AMC', 'Bangalore', 'Emily White')
SELECT * FROM DUAL;

-- Create Film table
CREATE TABLE FILM (
    FID NUMBER PRIMARY KEY,
    TITLE VARCHAR2(100),
    DIRECTOR_NAME VARCHAR2(100),
    GENRE VARCHAR2(100),
    BUDGET NUMBER(12, 2),
    RATING NUMBER(3, 1)
);

-- Insert sample data into Film
INSERT ALL 
INTO FILM VALUES (101, 'Avatar', 'James Cameron', 'Action', 237000000.00, 7.8)
INTO FILM VALUES (102, 'Titanic', 'James Cameron', 'Romance', 200000000.00, 7.8)
INTO FILM VALUES (103, 'Interstellar', 'Christopher Nolan', 'Sci-Fi', 165000000.00, 8.6)
INTO FILM VALUES (104, 'Inception', 'Christopher Nolan', 'Sci-Fi', 160000000.00, 8.8)
INTO FILM VALUES (105, 'The Dark Knight', 'Christopher Nolan', 'Action', 185000000.00, 9.0)
INTO FILM VALUES (106, 'DDLJ', 'Aditya Chopra', 'Romance', 10000000.00, 7.8)
INTO FILM VALUES (107, '3 Idiots', 'Rajkumar Hirani', 'Comedy', 30000000.00, 8.4)
SELECT * FROM DUAL;

-- Create showing table
CREATE TABLE SHOWING (
    FID NUMBER,
    CID NUMBER,
    CONSTRAINT SHK1 FOREIGN KEY (FID) REFERENCES FILM(FID),
    CONSTRAINT SHK2 FOREIGN KEY (CID) REFERENCES CINEMA(CID)
);

-- Insert sample data into Showing
INSERT ALL 
INTO SHOWING VALUES (101, 1)
INTO SHOWING VALUES (102, 1)
INTO SHOWING VALUES (103, 2)
INTO SHOWING VALUES (104, 2)
INTO SHOWING VALUES (105, 3)
INTO SHOWING VALUES (106, 3)
INTO SHOWING VALUES (107, 4)
SELECT * FROM DUAL;

-- QUERY 1
-- List the name, city, and the number of different films showing at each cinema/theatre; results 
-- should be returned in the ascending alphabetical order of city and name.

SELECT C.CNAME, C.CITY, COUNT(DISTINCT S.FID) AS NUMFILM
FROM CINEMA C
LEFT JOIN SHOWING S ON C.CID = S.CID
GROUP BY C.CNAME, C.CITY
ORDER BY C.CITY, C.CNAME;

-- QUERY 2
-- Find the titles and names of director/s of the blockbuster films running at every cinema/theatre, -- that has made an entry into the 100 - crore club.

SELECT F.TITLE, F.DIRECTOR_NAME
FROM FILM F
JOIN SHOWING S ON F.FID = S.FID
JOIN CINEMA C ON S.CID = C.CID
WHERE F.BUDGET > 100000000.00
GROUP BY F.TITLE , F.DIRECTOR_NAME
HAVING SUM(F.BUDGET) >= 100000000;

-- QUERY 3
-- Find the owners of theatres showing "romance" but not "comedy".

SELECT DISTINCT C.OWNER_NAME
FROM CINEMA C
JOIN SHOWING S ON C.CID = S.CID
JOIN FILM F ON S.FID = F.FID
WHERE F.GENRE = 'Romance'
AND C.CID NOT IN (
	SELECT DISTINCT C.CID
	FROM CINEMA C
	JOIN SHOWING S ON C.CID = S.CID
	JOIN FILM F ON S.FID = F.FID
	WHERE F.GENRE = 'Comedy'
);

-- QUERY 4
-- Out of all films showing in Mumbai, retrieve the film ID, title, and director of the films whose -- budget is more than the cheapest film showing in "Rajkot".

SELECT F.FID, F.TITLE, F.DIRECTOR_NAME
FROM FILM F
JOIN SHOWING S ON F.FID = S.FID
JOIN CINEMA C ON S.CID = C.CID
WHERE C.CITY = 'Mumbai'
AND F.BUDGET > (
	SELECT MIN(F2.BUDGET)
	FROM FILM F2
	JOIN SHOWING S2 ON F2.FID = S2.FID
	JOIN CINEMA C2 ON S2.CID = C2.CID
	WHERE C2.CITY = 'Rajkot'
);
