-- CREATE TABLES
CREATE TABLE DOCTOR (
    SSN VARCHAR2(10) PRIMARY KEY,
    FirstName VARCHAR2(50),
    LastName VARCHAR2(50),
    Specialty VARCHAR2(20),
    YearsOfExperience INT,
    PhoneNum VARCHAR2(15)
);

CREATE TABLE PATIENT (
    SSN VARCHAR2(10) PRIMARY KEY,
    FirstName VARCHAR2(50),
    LastName VARCHAR2(50),
    Address VARCHAR2(25),
    DOB DATE,
    PrimaryDoctor_SSN VARCHAR(10),
    CONSTRAINT PFK1 FOREIGN KEY (PrimaryDoctor_SSN) REFERENCES DOCTOR(SSN) ON DELETE CASCADE
);

CREATE TABLE MEDICINE (
    TradeName VARCHAR2(20) PRIMARY KEY,
    UnitPrice NUMBER(10,2),
    GenericFlag CHAR(1)
);

CREATE TABLE PRESCRIPTION (
    Id VARCHAR2(10) PRIMARY KEY,
    PDate DATE,
    Doctor_SSN VARCHAR2(10),
    Patient_SSN VARCHAR2(10),
    CONSTRAINT PNFK1 FOREIGN KEY (Doctor_SSN) REFERENCES DOCTOR(SSN) ON DELETE CASCADE,
    CONSTRAINT PNFK2 FOREIGN KEY (Patient_SSN) REFERENCES PATIENT(SSN) ON DELETE CASCADE
);

CREATE TABLE Prescription_Medicine (
    Prescription_Id VARCHAR2(10),
    TradeName VARCHAR2(20),
    NumOfUnits NUMBER,
    CONSTRAINT PMFK1 FOREIGN KEY (Prescription_Id) REFERENCES Prescription(Id) ON DELETE CASCADE,
    CONSTRAINT PMFK2 FOREIGN KEY (TradeName) REFERENCES Medicine(TradeName) ON DELETE CASCADE
);

-- INSERT VALUES
INSERT ALL 
INTO DOCTOR VALUES ('123456789', 'John', 'Smith', 'Cardiology', 15, '123-456-7890')
INTO DOCTOR VALUES ('234567890', 'Jane', 'Doe', 'Pediatrics', 10, '234-567-8901')
INTO DOCTOR VALUES ('345678901', 'David', 'Johnson', 'Orthopedics', 20, '345-678-9012')
INTO DOCTOR VALUES ('456789012', 'Emily', 'Brown', 'Oncology', 8, '456-789-0123')
INTO DOCTOR VALUES ('567890123', 'Michael', 'Davis', 'Internal Medicine', 12, '567-890-1234')
SELECT * FROM dual;

INSERT ALL 
INTO PATIENT VALUES ('111111111', 'Alice', 'Johnson', '123 Main St', TO_DATE('1990-05-15', 'YYYY-MM-DD'), '123456789')
INTO PATIENT VALUES ('222222222', 'Bob', 'Williams', '456 Elm St', TO_DATE('1985-08-20', 'YYYY-MM-DD'), '234567890')
INTO PATIENT VALUES ('333333333', 'Carol', 'Miller', '789 Oak St', TO_DATE('1975-12-10', 'YYYY-MM-DD'), '345678901')
INTO PATIENT VALUES ('444444444', 'David', 'Wilson', '101 Pine St', TO_DATE('2000-03-25', 'YYYY-MM-DD'), '456789012')
INTO PATIENT VALUES ('555555555', 'Emma', 'Brown', '202 Cedar St', TO_DATE('1998-09-30', 'YYYY-MM-DD'), '567890123')
SELECT * FROM dual;

INSERT ALL 
INTO MEDICINE VALUES ('Aspirin', 10.00, 'Y')
INTO MEDICINE VALUES ('Vitamin', 5.00, 'Y')
INTO MEDICINE VALUES ('Paracetamol', 15.00, 'N')
INTO MEDICINE VALUES ('Amoxicillin', 20.00, 'N')
INTO MEDICINE VALUES ('Ibuprofen', 8.00, 'Y')
SELECT * FROM dual;

INSERT ALL 
INTO PRESCRIPTION VALUES ('00001', TO_DATE('2024-03-19', 'YYYY-MM-DD'), '123456789', '111111111')
INTO PRESCRIPTION VALUES ('00002', TO_DATE('2024-03-20', 'YYYY-MM-DD'), '234567890', '222222222')
INTO PRESCRIPTION VALUES ('00003', TO_DATE('2024-03-21', 'YYYY-MM-DD'), '345678901', '333333333')
INTO PRESCRIPTION VALUES ('00004', TO_DATE('2024-03-22', 'YYYY-MM-DD'), '456789012', '444444444')
INTO PRESCRIPTION VALUES ('00005', TO_DATE('2024-03-23', 'YYYY-MM-DD'), '567890123', '555555555')
SELECT * FROM dual;

INSERT ALL 
INTO Prescription_Medicine VALUES ('00001', 'Aspirin', 2)
INTO Prescription_Medicine VALUES ('00002', 'Vitamin', 1)
INTO Prescription_Medicine VALUES ('00003', 'Paracetamol', 3)
INTO Prescription_Medicine VALUES ('00004', 'Amoxicillin', 2)
INTO Prescription_Medicine VALUES ('00005', 'Ibuprofen', 2)
SELECT * FROM dual;

-- I) List the trade name of generic medicine with a unit price less than $50.
SELECT TradeName
FROM MEDICINE
WHERE GenericFlag = 'Y' AND UnitPrice < 50;

-- II) List the first and last name of patients whose primary doctor is named 'John Smith'.
SELECT p.FirstName, p.LastName
FROM PATIENT p
JOIN DOCTOR d ON p.PrimaryDoctor_SSN = d.SSN
WHERE d.FirstName = 'John' AND d.LastName = 'Smith';

-- III) List the first and last name of doctors who are not primary doctors to any patient.
SELECT FirstName, LastName
FROM DOCTOR
WHERE SSN NOT IN (SELECT PrimaryDoctor_SSN FROM PATIENT WHERE PrimaryDoctor_SSN IS NOT NULL);

-- IV) For medicines written in more than 20 prescriptions, report the trade name and the total number of units prescribed.
SELECT pm.TradeName, SUM(pm.NumOfUnits) AS TotalUnits
FROM Prescription_Medicine pm
GROUP BY pm.TradeName
HAVING COUNT(pm.Prescription_Id) > 20;

-- V) List the SSN of patients who have 'Aspirin' and 'Vitamin' trade names in one prescription.
SELECT p.SSN
FROM PATIENT p
JOIN PRESCRIPTION pr ON p.SSN = pr.Patient_SSN
JOIN Prescription_Medicine pm ON pr.Id = pm.Prescription_Id
WHERE pm.TradeName IN ('Aspirin', 'Vitamin')
GROUP BY p.SSN
HAVING COUNT(DISTINCT pm.TradeName) = 2;

-- VI) List the SSN of distinct patients who have 'Aspirin' prescribed to them by a doctor named 'John Smith'.
SELECT DISTINCT p.SSN
FROM PATIENT p
JOIN PRESCRIPTION pr ON p.SSN = pr.Patient_SSN
JOIN DOCTOR d ON pr.Doctor_SSN = d.SSN
JOIN Prescription_Medicine pm ON pr.Id = pm.Prescription_Id
WHERE pm.TradeName = 'Aspirin' AND d.FirstName = 'John' AND d.LastName = 'Smith';
