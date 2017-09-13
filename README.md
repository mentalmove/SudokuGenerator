## Step III - Which Section

Now the opposite - row, column and small square shall be
assigned to a given index. The information will be stored
in an instance of

```
struct dimensions_collection {
	int row;
	int column;
	int small_square;
};
```

The responsible function is

```
struct dimensions_collection get_collection(unsigned int);
```

Fortunately, since the information is needed only for one index,
`get_collection()` looks much more like
`fill_rows()`, `fill_cols()` and `fill_small_squares()`
of the first example.

Displayed on screen, the result could look like

> Index 0 is in row 0, column 0, square 0  
> Index 1 is in row 0, column 1, square 0  
> Index 2 is in row 0, column 2, square 0  
> ...  
> Index 25 is in row 2, column 7, square 2  
> Index 26 is in row 2, column 8, square 2  
> Index 27 is in row 3, column 0, square 3  
> ...  
> Index 78 is in row 8, column 6, square 8  
> Index 79 is in row 8, column 7, square 8  
> Index 80 is in row 8, column 8, square 8
