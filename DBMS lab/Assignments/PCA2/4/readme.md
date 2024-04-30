```

Parts (PNO, Pnafme, Qoh, Price, OLevel) /*Qoh stands for quantity on hand*/
Customers (CNO, CName, Street, Zip, Phone)
Employees (ENO, EName, Zip, HDate)
Zip Codes (Zip, City)
Orders (ONO, CNO, ENO, Received, Shipped)
ODetails (ONO, PNO, Qty)

a) Create the tables and enter at least 5 sets of records in each table created that will help in retrieving data from your database.
b) Write the following queries in SQL. No duplicates should be printed in any of the answers. Output should display at least one record set.

1. Retrieve the names and cities of employees who have taken orders for parts costing more than $ 50.00.
2. Retrieve the pairs of customer number, customers who live in the same zip code. 
3. For every customer, who have ordered exactly '2' parts from employees living in 'Wellington', retrieve the part name and the price of the part.
4. Retrieve the names of customers who have not placed an order.

```
