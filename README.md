## Step IV - Solved Sudoku

To check if a number potentially to set already exists in row, column or small square,
the function
```c
unsigned int contains_element(unsigned int*, unsigned int, unsigned int);
```
is introduced: For the actual index, _row_, _column_ and _small square_ are discovered by
`get_collection()`, described in the last step; then the already set numbers
are retrieved by
`get_horizontal()`, `get_vertical()` and `get_square()`, explained in step 2;
finally, `contains_element()` checks if one of these numbers
is identical with the respective number.

---

When trying numbers for a given index, decision criteria are
> Number is bad if it already exists in same row, column or small square  
> Number is bad if it collides with prospective numbers in same row, column or small square

First decision can be made easily with the procedure described above;  
second decision can't be made directly **due to not knowing future numbers**.

There is only one situation where this problem can be circumvented:  
It is known that the last number to set is not dependent of prospective numbers;
after checking the last number to set against previous numbers,
the decision is incontrovertible.
	
Analogically, the second last number is only dependent of the last number;
it can be set on spec and then be validated against the last number.  
The third last number is dependent of the second last and the last number;
it can be set on spec and then be validated against the last two numbers etc.

&nbsp;

A generalised approach, inspired by the above idea, could be adding a return value
(_success_ or _unsuccess_) to a function trying to set values for a given index;
following the rule
> If number does not exist in same row, column or small square
> > return _**success** of next index_

Transformed to pseudo code:
```
Try all possible numbers
    If number already exists in same row, column or small square
        try next number
    If number is last number to set
        return SUCCESS
    If next number returns success
        return SUCCESS
Reset number set on spec
return UNSUCCESS
```

This is implemented in function 

```
unsigned int set_values(unsigned int);
```

---

Result will be a valid unsolved, but unfortunately boring sudoku:


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
| 6 : 4 : 2 | 9 : 7 : 8 | 5 : 3 : 1 |
|- - - - - -|- - - - - -|- - - - - -|
| 9 : 7 : 8 | 5 : 3 : 1 | 6 : 4 : 2 |
 ----------------------------------- 
```
