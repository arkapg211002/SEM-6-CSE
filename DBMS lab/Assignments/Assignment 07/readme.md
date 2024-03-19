```
I.Design an ER diagram for an application that models a hospital doctors treat patients, prescribe tests, monitor progress etc.
Analyze the requirements by identifying the entities, attributes, relationships, keys, constraints etc.
Apply extended entity-relationship features to the design. Defend your design with proper assumptions and justifications.
Map the ER model into a relational model.

II.Create tables, populate with data and construct queries (advanced) in SQL to extract information from the hospital doctor’s database.

III.Consider the following relations run the following SQL queries :
Doctor(SSN, FirstName, LastName, Specialty, YearsOfExperience, PhoneNum)
Patient(SSN, FirstName, LastName, Address, DOB, PrimaryDoctor_SSN)
Medicine(TradeName, UnitPrice, GenericFlag)
Prescription(Id, Date, Doctor_SSN, Patient_SSN)
Prescription_Medicine(Prescription Id, TradeName, NumOfUnits)

1.List the trade name of generic medicine with unit price less than $50.
2.List the first and last name of patients whose primary doctor named ʻJohn Smithʼ.
3.List the first and last name of doctors who are not primary doctors to any patient.
4.For medicines written in more than 20 prescriptions, report the trade name and the total number of units prescribed.
5.List the SSN of patients who have ʻAspirinʼ and ʻVitaminʼ trade names in one prescription.
6.List the SNN of distinct patients who have ʻAspirinʼ prescribed to them by doctor named ʻJohn Smithʼ.
7.List the first and last name of patients who have no prescriptions written by doctors other than their primary doctors. 
```
