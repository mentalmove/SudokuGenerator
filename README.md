## Step VIII - Square Rules

Diagonal indices were a good idea, but lack in flexibility.
Instead, the first `LINE` indices of the first small square shall be filled,
then the second `LINE` indices of the second small square etc.
Used function is
```c
void fill_small_squares(unsigned int*);
```
which looks a bit more frightening than its namesake of step 1
due to the fact that this time the numbers obviously must not be repeated.
In this basic appearance, it takes 3195 tries to generate a solved 9x9 sudoku
(what is worse than 405 tries the diagonal method needed
but still more than acceptable).  
The reason why it works well stays the same:
_Dead ends are detected very soon_.

&nbsp;

Randomisation is done only inside small squares;
to avoid further arithmetics, this time the
already generated indices are copied
and used for indexing.
Inside a block of `LINE` elements, every element
swaps its place with a higher one chosen by random.
```C
void shuffle_indices (unsigned int* indices) {
	unsigned int meta_indices[TOTAL];
	unsigned int i, j, random, tmp;
	for ( i = 0; i < TOTAL; i++ )
		meta_indices[i] = indices[i];
	for ( i = 0; i < LINE; i++ ) {
		for ( j = (i * LINE); j < ((i + 1) * LINE); j++ ) {
			random = rand() % ((i + 1) * LINE - j) + j;
			tmp = indices[meta_indices[j]];
			indices[meta_indices[j]] = indices[meta_indices[random]];
			indices[meta_indices[random]] = tmp;
		}
	}
}
```
&nbsp;

Original indices on the left, possible randomised version on the right:
```
 -------------------                                     -------------------
|  0 :  1 |  4 :  5 |                                   |  0 :  2 |  7 :  5 |
|- - - - -|- - - - -|                                   |- - - - -|- - - - -|
|  2 :  3 |  6 :  7 |                                   |  1 :  3 |  6 :  4 |
|---------+---------|                                   |---------+---------|
|  8 :  9 | 12 : 13 |                                   |  8 : 11 | 15 : 14 |
|- - - - -|- - - - -|                                   |- - - - -|- - - - -|
| 10 : 11 | 14 : 15 |                                   | 10 :  9 | 13 : 12 |
 -------------------                                     -------------------
 ```
 
 
 
 ```
 --------------------------------------------            --------------------------------------------
|  0 :  1 :  2 |  9 : 10 : 11 | 18 : 19 : 20 |          |  2 :  4 :  3 | 16 : 15 :  9 | 25 : 22 : 19 |
|- - - - - - - |- - - - - - - |- - - - - - - |          |- - - - - - - |- - - - - - - |- - - - - - - |
|  3 :  4 :  5 | 12 : 13 : 14 | 21 : 22 : 23 |          |  7 :  0 :  1 | 10 : 13 : 11 | 23 : 20 : 18 |
|- - - - - - - |- - - - - - - |- - - - - - - |          |- - - - - - - |- - - - - - - |- - - - - - - |
|  6 :  7 :  8 | 15 : 16 : 17 | 24 : 25 : 26 |          |  8 :  6 :  5 | 17 : 12 : 14 | 24 : 26 : 21 |
|--------------+--------------+--------------|          |--------------+--------------+--------------|
| 27 : 28 : 29 | 36 : 37 : 38 | 45 : 46 : 47 |          | 31 : 29 : 28 | 42 : 39 : 43 | 49 : 46 : 52 |
|- - - - - - - |- - - - - - - |- - - - - - - |          |- - - - - - - |- - - - - - - |- - - - - - - |
| 30 : 31 : 32 | 39 : 40 : 41 | 48 : 49 : 50 |          | 30 : 34 : 33 | 37 : 41 : 40 | 51 : 50 : 53 |
|- - - - - - - |- - - - - - - |- - - - - - - |          |- - - - - - - |- - - - - - - |- - - - - - - |
| 33 : 34 : 35 | 42 : 43 : 44 | 51 : 52 : 53 |          | 35 : 27 : 32 | 44 : 36 : 38 | 45 : 48 : 47 |
|--------------+--------------+--------------|          |--------------+--------------+--------------|
| 54 : 55 : 56 | 63 : 64 : 65 | 72 : 73 : 74 |          | 62 : 54 : 59 | 69 : 71 : 65 | 80 : 78 : 75 |
|- - - - - - - |- - - - - - - |- - - - - - - |          |- - - - - - - |- - - - - - - |- - - - - - - |
| 57 : 58 : 59 | 66 : 67 : 68 | 75 : 76 : 77 |          | 61 : 56 : 57 | 70 : 63 : 68 | 76 : 73 : 72 |
|- - - - - - - |- - - - - - - |- - - - - - - |          |- - - - - - - |- - - - - - - |- - - - - - - |
| 60 : 61 : 62 | 69 : 70 : 71 | 78 : 79 : 80 |          | 55 : 60 : 58 | 64 : 67 : 66 | 77 : 79 : 74 |
 --------------------------------------------            --------------------------------------------
```

---

The suitability of this procedure can easily be checked
by executing the application
but as well be understood theoretically:
- Indices are still more or less adjacent even after randomisation - failures will be detected early.
- Since small squares contain `LINE` numbers in any case,
the probability for every number to appear on a distinct place
is the same as with complete randomisation.

---

**Branch _master_** will contain only two small variations:  
Firstly, as a further performance improvement,
small squares shall be handled in an order
such that every following small square
shall be neighboured to its predecessor.  
Secondly, since the previously described method
allows different variations, one of these will be chosen by random
to provide more (optical) variety to the user.
