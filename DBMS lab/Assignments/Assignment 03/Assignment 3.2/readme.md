The Prescriptions-R-X chain of pharmacies has offered to give you a free life-time supplyof medicines if you design its database. Given the rising cost of health care, you agree.Here is the information that you gather.

1. Patients are identified by SSN, and their names, addresses, and also ages.

2. Doctors are identified by an SSN, for each doctor, the name, specialty and years ofexperience must be recorded.

3. Each pharmaceutical company is identified by name and has a phone number.

4. For each drug, the trade name and formula must be recorded. Each drug is sold by agiven pharmaceutical company, and the trade name identifies a drug uniquely fromamong the products of that company. If a pharmaceutical company is deleted, you neednot keep track of its products any longer.

5. Each pharmacy has a name, address, and phone number.

6. Every patient has a primary physician. Every doctor has at least one patient.

7. Each pharmacy sells several drugs and has a price for each. A drug could be sold atseveral pharmacies, and the price could vary from one pharmacy to another.

8. Doctors prescribe drugs for patients. A doctor could prescribe one or more drugs forseveral patients, and a patient could obtain prescriptions from several doctors. Each prescription has a date and a quantity associated with it. You can assume that if a doctor prescribes the same drug for the same patient more than once, only the last such prescription needs to be stored.

9. Pharmaceutical company have long-term contracts with pharmacies. A pharmaceuticalcompany can contract with several pharmaceutical companies. For each contract, youhave to store a start date, and end date, and the text of the contract.

10. Pharmacies appoint a supervisor for each contract. There must always a supervisor  for each contract.-

End of the Spec. Tasks:

1. Draw a ER diagram that captures the above information. Identify and contraints thatare not captured by your ER-diagram.

2. How would your design change if each drug must be sold at a fixed price by all the pharmacies?

3. How would your design change if the design requirements change as follows: If adoctor prescribes the same drug for the same patient more than once, several such prescriptions may have to be stored separately?
