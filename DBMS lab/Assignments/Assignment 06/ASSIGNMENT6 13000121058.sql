/*

Create  tables,  populate  with  data  and  construct  queries  (advanced)  in  SQL  to  extract 
information from the car insurance company’s database.Consider a car-insurance company whose customers 
own one or more cars each. Each car has associated with it zero to any number of recorded accidents.

*/

-- CREATE TABLES
CREATE TABLE CUSTOMER (
    CID VARCHAR2(8) PRIMARY KEY CONSTRAINT C1 CHECK(CID LIKE 'C%'),
    NAME VARCHAR2(20),
    ADDRESS VARCHAR2(20),
    PNO VARCHAR2(20)
);

CREATE TABLE CAR (
    LNO VARCHAR2(10) PRIMARY KEY ,
    MODEL VARCHAR2(20),
    CID VARCHAR2(8),
    CONSTRAINT CARFK1 FOREIGN KEY (CID) REFERENCES CUSTOMER(CID) ON DELETE CASCADE
);

CREATE TABLE ACCIDENT (
    RNO VARCHAR2(10) PRIMARY KEY,
	LNO VARCHAR2(10),
    ADATE DATE,
    DAMOUNT NUMBER(10, 2),
	CONSTRAINT AFK1 FOREIGN KEY (LNO) REFERENCES CAR(LNO) ON DELETE CASCADE
);

CREATE TABLE Comprehensive_Car (
    LNO VARCHAR2(10),
    INSURANCE_TYPE VARCHAR2(20),
    CONSTRAINT CCFK1 FOREIGN KEY (LNO) REFERENCES CAR(LNO) ON DELETE CASCADE
);

CREATE TABLE Third_Party_Car (
    LNO VARCHAR2(10),
    TINSURANCE_TYPE VARCHAR(50), 
    CONSTRAINT TPCFK1 FOREIGN KEY (LNO) REFERENCES CAR(LNO) ON DELETE CASCADE
);

-- INSERT VALUES
-- CUSTOMER
INSERT ALL
INTO CUSTOMER VALUES ('C1', 'ARKA', 'AC-13', '9330450430')
INTO CUSTOMER VALUES ('C2', 'RAMU', 'BD-20', '8910062339')
INTO CUSTOMER VALUES ('C3', 'JADU', 'CC-21', '9007523577')
INTO CUSTOMER VALUES ('C4', 'SIDD', 'CC-10', '7014561289')
INTO CUSTOMER VALUES ('C5', 'JOHN', 'EF-13', '8910120012')
SELECT * FROM DUAL;

-- CAR
INSERT ALL
INTO CAR VALUES ('AIAPC2010', 'Toyota Camry', 'C1')
INTO CAR VALUES ('AIDPC2010', 'Scorpio', 'C2')
INTO CAR VALUES ('AICPC2010', 'Ford Mustang', 'C3')
INTO CAR VALUES ('AIEPC2010', 'Chevrolet Cruze', 'C4')
INTO CAR VALUES ('AIBPC2010', 'BMW X5', 'C5')
SELECT * FROM DUAL;

-- ACCIDENT
INSERT ALL
INTO ACCIDENT VALUES ('FIR001', 'AIAPC2010', TO_DATE('19-03-2024', 'DD-MM-YYYY'), 15000.00)
INTO ACCIDENT VALUES ('FIR002', 'AIDPC2010', TO_DATE('20-03-2024', 'DD-MM-YYYY'), 20000.00)
INTO ACCIDENT VALUES ('FIR003', 'AICPC2010', TO_DATE('21-03-2024', 'DD-MM-YYYY'), 18000.00)
INTO ACCIDENT VALUES ('FIR004', 'AIEPC2010', TO_DATE('22-03-2024', 'DD-MM-YYYY'), 22000.00)
INTO ACCIDENT VALUES ('FIR005', 'AIBPC2010', TO_DATE('23-03-2010', 'DD-MM-YYYY'), 25000.00)
SELECT * FROM DUAL;

-- COMPREHENSIVE CAR
INSERT ALL
INTO Comprehensive_Car VALUES ('AIAPC2010', 'Comprehensive1')
INTO Comprehensive_Car VALUES ('AIDPC2010', 'Comprehensive2')
INTO Comprehensive_Car VALUES ('AICPC2010', 'Comprehensive3')
INTO Comprehensive_Car VALUES ('AIEPC2010', 'Comprehensive3')
INTO Comprehensive_Car VALUES ('AIBPC2010', 'Comprehensive1')
SELECT * FROM DUAL;

-- THIRD PARTY CAR
INSERT ALL
INTO Third_Party_Car VALUES ('AIAPC2010', 'Third-Party1')
INTO Third_Party_Car VALUES ('AIDPC2010', 'Third-Party1')
INTO Third_Party_Car VALUES ('AICPC2010', 'Third-Party3')
INTO Third_Party_Car VALUES ('AIEPC2010', 'Third-Party2')
INTO Third_Party_Car VALUES ('AIBPC2010', 'Third-Party2')
SELECT * FROM DUAL;

-- a. Find the total number of people who owned cars that were involved in accidents in 2010.
SELECT COUNT(C.CID) FROM CUSTOMER C 
JOIN CAR CA ON CA.CID=C.CID
JOIN ACCIDENT A ON A.LNO =  CA.LNO
WHERE EXTRACT(YEAR FROM A.ADATE)=2010;

-- b. Find the number of accidents in which the cars belonging to “XYZ” were involved. 
SELECT COUNT(*) AS Total_Accidents
FROM ACCIDENT A
JOIN CAR CA ON A.LNO = CA.LNO
JOIN CUSTOMER C ON CA.CID = C.CID
WHERE C.NAME = 'XYZ';

-- c. Add a new accident to the database; assume any values for required attributes. 
INSERT INTO ACCIDENT (RNO, LNO, ADATE, DAMOUNT) 
VALUES ('FIR006', 'AIAPC2010', TO_DATE('12-02-2010', 'DD-MM-YYYY'), 20000.00);

-- d. Delete the model ‘Scorpio belonging to “ABC”. 
DELETE FROM CAR WHERE MODEL = 'Scorpio' AND CID = 'ABC';

-- e. Update the damage amount for the car with license number “AIBPC2010” in the accident with report number “FIR271” to Rs. 5000. 
UPDATE ACCIDENT
SET DAMOUNT = 5000
WHERE RNO = 'FIR271' AND LNO = 'AIBPC2010';
