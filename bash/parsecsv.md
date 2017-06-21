# Parse a CSV

This exercise is basicly parsing a csv. There are multiple ways to do this. I recommend trying the cut command and the use of arrays to exercise using external commands in a script as well as some programming paradigms used in other languages.


Create a script.sh. When we run ``script.sh data.csv`` the output should be as follows:

```
Total revenue between 17/06/2017 and 21/06/2017 is: 290,00.
Most artikels were sold On 21/06/2017 (3).
Between 17/06/2017 and 21/06/2017 Final Fantasy XV was sold 3 times.
```

Basicly we want 3 lines of output: 
- The first one stating the total revenu (the sum of all prices in the fifth column).
- The second one telling us the date that has the most entries.
- The third one telling us the title of the game that has been sold the most.

Hints that might help:
- cut, sort, nl, wc
- The range is always the earliest date and the latest date.

**Contents of data.csv:**

```csv
id;date;console;title;price
1;21/06/2017;ps4;Persona 5;50,00
2;21/06/2017;ps4;Final Fantasy XV;50,00
3;21/06/2017;ps4;Kingdom Hearts 1.5 + 2.5;40,00
4;20/06/2017;pc;Life is strange;30,00
5;19/06/2017;pc;Final Fantasy XIII;20,00
6;18/06/2017;ps4;Final Fantasy XV;50,00
7;17/06/2017;ps4;Final Fantasy XV;50,00
```
