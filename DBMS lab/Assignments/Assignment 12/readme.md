```
Hotel (Hotel_No, Name, Address)
Room (Room_No, Hotel_No, Type, Price)
Booking (Hotel_No, Guest_No, Date_From, Date_To, Room_No)
Guest (Guest_No, Name, Address)

Populate the tables Answer the following query using SQL.
1.List the names and addresses of all guests in London, alphabetically ordered by name
2.List all double or family rooms with a price below £40.00 per night, in ascending order of price.
3.List the bookings for which no date_to has been specified.
4.How many hotels are there?
5.What is the average price of a room?
6.What is the total revenue per night from all double rooms?
7.How many different guests have made bookings for August?
8.List the details of all rooms at the Grosvenor Hotel, including the name of the guest staying in the room, if the room is occupied.
9.What is the total income from bookings for the Grosvenor Hotel today?
10.List the rooms that are currently unoccupied at the Grosvenor Hotel.

Design an ER Model for an application where hotels are booked by guests wanting to go on aholiday in India or abroad. Your design should meet all requirements. Map into a relationalmodel.
```

```
EMPLOYEE (SSN, Name, Address, Sex, Salary, SuperSSN, DNo)
DEPARTMENT (DNo, DName, MgrSSN, MgrStartDate)
DLOCATION (DNo,DLoc)
PROJECT (PNo, PName, PLocation, DNo)
WORKS_ON (SSN, PNo, Hours)

Write SQL queries to ............
1.Make a list of all project numbers for projects that involve an employee whose last name is ‘Scott’, either as a worker or as a manager of the department that controls the project.
2.Show the resulting salaries if every employee working on the ‘IoT’ project is given a 10 percent raise.
3.Find the sum of the salaries of all employees of the ‘Accounts’ department, as well as the maximum  salary, the minimum salary, and the average salary in this department
4.Retrieve the name of each employee who works on all the projects controlled by department number

5 (use NOT EXISTS operator).
5.For each department that has more than five employees, retrieve the department number and the number of its employees who are making more than Rs. 6,00,000.

B. Write a program in PL/SQL to create a procedure to displays the GCD of nos.

C.Write a program in PL/SQL to create a cursor displays the name and salary of each employee in the EMPLOYEES table whose salary is less than that specified by a passed-in parameter value. 
```
