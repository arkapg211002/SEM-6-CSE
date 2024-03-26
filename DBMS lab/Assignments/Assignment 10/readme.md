```
Consider the following tables:
MATCH (match_id, team1, team2, ground, mdate, winner)
PLAYER (p_id, lname, fname, country, yborn, bplace, ftest)
BATTING (match_id, p_id, mts, order, out_type, fow, nruns, nballs, fours, sixes)
BOWLING (match_id, p_id, novers, maidens, nruns, nwickets)

1.Draw the appropriate ER, EER and Relational model for the given data.

2.Write SQL expressions for the following:
  i)Find match ids of those matches in which player 27001 bats and makes more runs than he made at every match he played at Sydney.
  ii)Find player ids of players who have scored more than 30 in every ODI match that they have batted.
  iii)Find the ids of players that had a higher average score than the average score for all players when they played in Sri Lanka.
```
