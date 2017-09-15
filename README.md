## Step VI - Unsolved Sudoku

Independent of the performance problems of the previous step,
an unsolved sudoku now shall be generated based on a given
solved sudoku.

Therefore, the additional parameter `forbidden_number` is added to `set_values()`:
```c
unsigned int set_values(unsigned int index, unsigned int forbidden_number);
```

Its meaning is:
> If the actual number to try is identical to `forbidden_number`, discard this try

<sup>(as if the number was part of _row_, _column_ or _small square_).</sup>

Since `forbidden_number` is always set to `0` while building a solved sudoku,
the new parameter has no influence during build.

&nbsp;

Numbers shall be erased one by one as long as not more than a single solution is possible.
This could be done in any order; to simplify things
and to provide a visible relationship between mechanism and output,
reverse order of setting is used here.  
Responsible is function
```c
void take_back(unsigned int);
```
```
Store the value of a given index
Try to complete the sudoku without using the stored value at this index
If operation fails                  // i.e. SUCCESS (we hope it fails, that guarantees uniqueness)
    Delete the value at this index
    Repeat with another index
Else
    Restore value at index
    Ensure previously deleted values stay deleted
```

The boring solved sudoku of step 4 will be transformed
to the following unsolved sudoku, boring as well:
```
 -----------------------------------
| 1 : 2 : 3 | 4 : 5 : 6 | 7 : 8 : 9 |
|- - - - - -|- - - - - -|- - - - - -|
| 4 : 5 : 6 | 7 : 8 : 9 | 1 : 2 : 3 |
|- - - - - -|- - - - - -|- - - - - -|
| 7 : 8 : 9 | 1 : 2 : 3 | 4 : 5 : 6 |
|-----------+-----------+-----------|
| 2 : 1 : 4 | 3 : 6 : 5 | 8 : 9 : 7 |
|- - - - - -|- - - - - -|- - - - - -|
| 3 : 6 : 5 | 8 : 9 : 7 | 2 : 1 : 4 |
|- - - - - -|- - - - - -|- - - - - -|
| 8 : 9 : 7 | 2 : 1 : 4 | 3 : 6 : 5 |
|-----------+-----------+-----------|
| 5 : 3 : 1 | 6 : 4 : 2 | 9 : 7 : 8 |
|- - - - - -|- - - - - -|- - - - - -|
| 6 : 4 : 2 |   :   :   |   :   :   |
|- - - - - -|- - - - - -|- - - - - -|
|   :   :   |   :   :   |   :   :   |
 ----------------------------------- 
```

---

When used this way, `take_back()` stops at the first value to take back
which allows more than one solution. When constant `REPEATED_TRIES`
is set to `1`, it will try to take back another value instead. In this case,
a global counter variable has to ensure that every value to potentially take back
must be tried only once. Result will be
```
 -----------------------------------
| 1 : 2 : 3 | 4 : 5 : 6 | 7 : 8 :   |
|- - - - - -|- - - - - -|- - - - - -|
| 4 : 5 : 6 | 7 : 8 :   | 1 : 2 :   |
|- - - - - -|- - - - - -|- - - - - -|
| 7 : 8 :   | 1 : 2 :   | 4 : 5 :   |
|-----------+-----------+-----------|
| 2 : 1 : 4 | 3 : 6 : 5 | 8 :   :   |
|- - - - - -|- - - - - -|- - - - - -|
| 3 : 6 : 5 | 8 :   :   |   : 1 :   |
|- - - - - -|- - - - - -|- - - - - -|
| 8 :   :   |   : 1 :   | 3 :   :   |
|-----------+-----------+-----------|
| 5 : 3 : 1 | 6 : 4 : 2 |   :   :   |
|- - - - - -|- - - - - -|- - - - - -|
| 6 : 4 : 2 |   :   :   |   :   :   |
|- - - - - -|- - - - - -|- - - - - -|
|   :   :   |   :   :   |   :   :   |
 -----------------------------------
```
