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

{%ace edit=true, lang='sh', theme='monokai'%}


#!/bin/bash

if [[ $# -lt 1 ]]; 
then
	printf "please give a csv-file as first param!\n";
else
	
	# printf "contents of the csv file:\n";
	# cat $1;
	# echo;

	ids=($(cat $1 | tail -n +2 | cut -d ';' -f 1));
	dates=($(cat $1 | tail -n +2 | cut -d ';' -f 2));
	consoles=($(cat $1 | tail -n +2 | cut -d ';' -f 3));
	titels=($(cat $1 | tail -n +2 | cut -d ';' -f 4));
	prizes=($(cat $1 | tail -n +2 | cut -d ';' -f 5));

	sum=0;

	for i in "${prizes[@]}"
	do :
		$sum+=$i;
	done

	echo $sum;

	begin="${dates[0]}";
	eind="${dates[-1]}";
	interval="%s and %s";



	
	bigdata=$begin;
	amountday=3;
	bigamount=3;
	title=aa;

	printf "Total revenue between $interval is: %d.\n" $begin $eind $sum;
	printf "Most artikels were sold on %s (%d).\n" $bigdata $amountday;
	printf "Between $interval %s was sold %d times.\n" $begin $eind $title $bigamount;

fi



{%endace%}