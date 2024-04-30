```

person (driver_id, name, address)
car (registration number, model, year)
accident (report no, date, location)
owns (driver_id, registration number)
participated in (driver_id, registration number, report no, damage_amount)

a) Create the tables and enter at least 5 sets of records in each table created that will help in retrieving data from your database.
b) Write optimized queries for the following. No duplicates should be printed in any of the answers. Output should display at least one record set.

1. Find the number of people who owned new cars that were involved in accidents in the year 2005 at "Mumbai"
2. For every accident that look place in "Kolkata" and on "15-06-2001" retrieve the driver details, and the amount of damage.
3. For the "Toyota" belonging to "Huffman", find the accidents that took place in "Delhi" but not in "Pune".
4. For every person who owns more than 2 cars, find the details for those cars which incurred a damage of Rs.50000 and above for accidents that took place in 2005.

```
