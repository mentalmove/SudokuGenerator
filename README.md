## Step I - Create And Show

`TOTAL` is the amount of possible positions (in a common sudoku `9 * 9 = 81`);
`LINE` is the square root of `TOTAL` (i.e. the side length of the complete sudoku);
`SMALL_LINE` is the square root of `LINE` (i.e. the side length of a small square).  
They are written uppercase since they usually would be constants
(in this example their values change during execution for demonstration purpose).

---

```c
void show_solution(unsigned int*)
```

with its helper functions

```c
void border_line();
void solid_line();
void dotted_line();
```

just displays a (solved or unsolved) sudoku;
it mainly prints the the linear collection on the screen,
adding a line break after `LINE` symbols
(and additionally some decoration).

---

`unsigned int* sudoku` is a collection to be filled
with symbols (following common convention positive integer numbers).
The collection is created as a linear
and not as a multidimensional array for two reasons:
- In fact, so-called _multidimensional_ arrays do not reflect
multiple dimensions; one is always dependent of another
while rows and columns shall be really equivalent here.
- Small squares do not reflect a dimension in a common
meaning of the word at all.

Therefore, if needed, the linear collection will be
transformed temporarily.

---

General sudoku rule is
> Every symbol shall appear in every row, every column
> and every small square exactly once.

&nbsp;

Functions

```c
void fill_rows(unsigned int*);
void fill_cols(unsigned int*);
void fill_small_squares(unsigned int*);
```

create sudokus where each one of the rules meets the requirements
while the two others fail;
this might seem trivial, but the underlying arithmetic
will be used later to get all positions
related to a distinct row, column or small square.
