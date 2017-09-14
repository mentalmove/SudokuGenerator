## Step II - Get Sections

For demonstrating purpose, valid solved sudokus are provided:

```
 ---------------             -----------------------------------
| 1 : 2 | 4 : 3 |           | 1 : 6 : 7 | 2 : 9 : 5 | 8 : 4 : 3 |
|- - - -|- - - -|           |- - - - - -|- - - - - -|- - - - - -|
| 4 : 3 | 1 : 2 |           | 5 : 8 : 4 | 3 : 7 : 6 | 1 : 2 : 9 |
|-------+-------|           |- - - - - -|- - - - - -|- - - - - -|
| 2 : 4 | 3 : 1 |           | 2 : 9 : 3 | 1 : 4 : 8 | 6 : 7 : 5 |
|- - - -|- - - -|           |-----------+-----------+-----------|
| 3 : 1 | 2 : 4 |           | 4 : 3 : 1 | 6 : 8 : 2 | 9 : 5 : 7 |
 ---------------            |- - - - - -|- - - - - -|- - - - - -|
                            | 7 : 2 : 6 | 9 : 5 : 3 | 4 : 8 : 1 |
                            |- - - - - -|- - - - - -|- - - - - -|
                            | 9 : 5 : 8 | 7 : 1 : 4 | 3 : 6 : 2 |
                            |-----------+-----------+-----------|
                            | 8 : 1 : 9 | 4 : 2 : 7 | 5 : 3 : 6 |
                            |- - - - - -|- - - - - -|- - - - - -|
                            | 3 : 4 : 2 | 5 : 6 : 1 | 7 : 9 : 8 |
                            |- - - - - -|- - - - - -|- - - - - -|
                            | 6 : 7 : 5 | 8 : 3 : 9 | 2 : 1 : 4 |
                             -----------------------------------
```

&nbsp;

The functions

```c
void get_horizontal(unsigned int, unsigned int*);
void get_vertical(unsigned int, unsigned int*);
void get_square(unsigned int, unsigned int*);
```

collect all elements of a given row, column or small square:

> Row 0 contains 1, 6, 7, 2, 9, 5, 8, 4, 3  
> Row 1 contains 5, 8, 4, 3, 7, 6, 1, 2, 9  
> ...  
> Column 0 contains 1, 5, 2, 4, 7, 9, 8, 3, 6  
> Column 1 contains 6, 8, 9, 3, 2, 5, 1, 4, 7  
> ...  
> Square 0 contains 1, 6, 7, 5, 8, 4, 2, 9, 3  
> Square 1 contains 2, 9, 5, 3, 7, 6, 1, 4, 8  
> ...

They use the same arithmetic principles as 
`fill_rows()`, `fill_cols()` and `fill_small_squares()`
of the last step but look a little more frightening
due to the fact that they deal with
`LINE` instead of `TOTAL` elements.  
They will be used later to check if a potentially to set number
collides with previously set ones - the only difference
will be filling a collection instead of just printing.
