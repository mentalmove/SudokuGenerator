## Step V - Introducing Indices

If the generated sudokus shall be worth playing more than once,
they need variety - the numbers to try have to be randomised somehow.
Generally, in C language, the random engine needs to be initialised
with an external value, usually a timestamp:
```c
time_t t;
time(&t);
srand((unsigned int) t);
```
Maybe the number of possible combinations is less than the
number of valid sudoku permutations, but it still should be high.

There are two possibilities to generate a randomised sudoku:
- Places in fixed order, numbers to try in random order
- Places in random order, numbers to try in fixed order

The second method is more recommendable because the first one has the following disadvantages:
- If the random order is identical for all places, sudokus will look differently but contain the same logic.
- If the random order is individual for all places, it must be stored to avoid repeated fails.
- When numbers are erased to create an unsolved sudoku, this method is useless
because the number to erase is already determined.

&nbsp;

For demonstrating purpose, the result of the previous step
shall be retrieved using indices.
Therefore, a collection of numbers must be set to values from `0` to `TOTAL - 1`:
```c
unsigned int i;
unsigned int* indices = malloc(TOTAL * sizeof(unsigned int));
for ( i = 0; i < TOTAL; i++ )
    indices[i] = i;
```
In function `set_values()`, the index to use must be defined as _value at position **index**_, e.g.
```c
unsigned int real_index = indices[index];
```
and every further occurence of `index` has to be exchanged with `real_index`.

&nbsp;

Randomisation of collection `indices` can be done by exchanging every
value with a value of higher index:
```c
unsigned int random, tmp;
for ( i = 0; i < TOTAL; i++ ) {
    random = rand() % (TOTAL - i) + i;
    tmp = indices[i];
    indices[i] = indices[random];
    indices[random] = tmp;
}
```

From a logical point of view, nothing is wrong with this.
Unfortunately, for a 9x9 sudoku, it probably takes unreasonable time
what easily can be checked by setting constant `PATIENCE` to `1`.
