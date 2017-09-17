## Step VII - Different Indices

At least in theory, the generator application is ready:  
It is able to produce a vaild unsolved sudoku -
unfortunately always the same.  
This disadvantage could be compensated using randomisation,
explained in step 5.

Without improvements, this suggestion lacks in practical relevance.  
A suitable collection of indices should have at least three properties:
- It should offer variety, i.e. be strongly randomised
- It should enable building a sudoku in reasonable time
- It should lead to an interesting sudoku, i.e. one with few remaining numbers

Fortunately, the two last points are correlated:
Creating a solved sudoku and transforming it to an unsolved sudoku
use the same functionality; problems finding valid numbers
and problems erasing numbers should have identical reasons.
In other words: Solving one of these problems should
solve the other.

### Example indices

Before diving into theoretical considerations, two different
collections of indices shall be examined.

&nbsp;

In the first one, indices walk diagonally:
#### Easy to solve
```c
unsigned int i;
unsigned int* indices = malloc(TOTAL * sizeof(unsigned int));
indices[0] = 0;
for ( i = 1; i < TOTAL; i++ )
    indices[i] = (indices[i - 1] + LINE + 1) % TOTAL;
```
Displayed graphically:
```
 --------------------------------------------
|  0 : 10 : 20 | 30 : 40 : 50 | 60 : 70 : 80 |
|- - - - - - - |- - - - - - - |- - - - - - - |
|  9 : 19 : 29 | 39 : 49 : 59 | 69 : 79 :  8 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 18 : 28 : 38 | 48 : 58 : 68 | 78 :  7 : 17 |
|--------------+--------------+--------------|
| 27 : 37 : 47 | 57 : 67 : 77 |  6 : 16 : 26 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 36 : 46 : 56 | 66 : 76 :  5 | 15 : 25 : 35 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 45 : 55 : 65 | 75 :  4 : 14 | 24 : 34 : 44 |
|--------------+--------------+--------------|
| 54 : 64 : 74 |  3 : 13 : 23 | 33 : 43 : 53 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 63 : 73 :  2 | 12 : 22 : 32 | 42 : 52 : 62 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 72 :  1 : 11 | 21 : 31 : 41 | 51 : 61 : 71 |
 --------------------------------------------
```
It needs only 405 steps to build a solved sudoku using `indices`.

&nbsp;

In the second one, even and odd indices are told apart:
#### More or less impossible to solve
```c
unsigned int determined;
for ( i = 0; i < TOTAL; i++ ) {
    determined = (2 * i) % TOTAL;
    if ( i >= (TOTAL / 2) && (TOTAL % 2) == 0 )         // For TOTAL being even only 
        determined++;
    indices[i] = determined;
}
```
Displayed graphically:
``` 
  --------------------------------------------
|  0 :  2 :  4 |  6 :  8 : 10 | 12 : 14 : 16 |
|--------------+--------------+--------------|
| 18 : 20 : 22 | 24 : 26 : 28 | 30 : 32 : 34 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 36 : 38 : 40 | 42 : 44 : 46 | 48 : 50 : 52 |
|--------------+--------------+--------------|
| 54 : 56 : 58 | 60 : 62 : 64 | 66 : 68 : 70 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 72 : 74 : 76 | 78 : 80 :  1 |  3 :  5 :  7 |
|- - - - - - - |- - - - - - - |- - - - - - - |
|  9 : 11 : 13 | 15 : 17 : 19 | 21 : 23 : 25 |
|--------------+--------------+--------------|
| 27 : 29 : 31 | 33 : 35 : 37 | 39 : 41 : 43 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 45 : 47 : 49 | 51 : 53 : 55 | 57 : 59 : 61 |
|- - - - - - - |- - - - - - - |- - - - - - - |
| 63 : 65 : 67 | 69 : 71 : 73 | 75 : 77 : 79 |
 --------------------------------------------
```
In human standards, the function never terminates what easily can be checked by setting constant `PATIENCE` to `1`.

&nbsp;

### Explanation

Understanding why the second example needs many steps is easier than understanding why the first example is frugal.

&nbsp;

```
 -----------------------------------
| 1 : 8 : 2 | 7 : 3 :   | 4 :   : 5 |
|- - - - - -|- - - - - -|- - - - - -|
|   : 3 :   | 1 :   : 2 |   : 6 :   |
|- - - - - -|- - - - - -|- - - - - -|
| 4 :   : 5 |   : 6 :   | 1 :   : 2 |
|-----------+-----------+-----------|
|   : 1 :   | 2 :   : 3 |   : 4 :   |
|- - - - - -|- - - - - -|- - - - - -|
| 2 :   : 3 |   : 1 :   | 5 :   : 6 |
|- - - - - -|- - - - - -|- - - - - -|
|   : 4 :   | 5 :   : 6 |   : 1 :   |
|-----------+-----------+-----------|
| 3 :   : 1 |   : 2 :   | 6 :   : 4 |
|- - - - - -|- - - - - -|- - - - - -|
|   : 2 :   | 3 :   : 1 |   : 5 :   |
|- - - - - -|- - - - - -|- - - - - -|
| 5 :   : 4 |   : 9 :   | 2 :   : 3 |
 ----------------------------------- 	 After 2006 tries 
```

As long as there are free spaces beneath every place holding a number,
the algorithm finds suitable seeming new numbers without difficulties.
The problem is that some of the chosen numbers disable any possibility
for their neighbours - but the relevant indices are not neighboured at all!
When reaching a dead end, the algorithm goes one step back, tries some
possibilities, goes to the dead end again, will fail and go back...  
Even if there were only 2 choices for every place
(there are obviously more when using 9 numbers),
repairing a single dead end's cause would cost more than
2<sup>40</sup> = 1099511627776 steps.

The general rule for problems like this is
> The effective runtime for recursive backtracking functions
> is exponentially proportional to the distance between
> a failure and its detection.

This also explains why the first example doesn't show a performance problem:
Causing dead ends will have almost immediate influence
(and can be repaired soon).

&nbsp;

Simplified, the moral is:
> If failing can't be avoided, fail early.
