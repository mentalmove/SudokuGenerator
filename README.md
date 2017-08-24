# Sudoku Generator

Generally, it is not difficult to create a Sudoku Generator Application.

In a first step, a recursive function creates a solved sudoku
by trying suitable numbers until all positions are filled.  
In a second step, the found numbers are erased one by one;
the same recursive function checks if it is possible to solve
the game with another number than the erased one.
If so, the respective number has to be restored, and the
sudoku is ready to play.

Unfortunately, when this method is used with random numbers,
it has - although working - two disadvantages:
- It usually takes unreasonable time to to finish
- Sudokus created this way usually are very easy to solve

By thinking deeply about it, a correlation
between the two disadvantages can be detected, but that
doesn't improve the situation.

A common solution is to provide a single sudoku
known to be adequately difficult and than swap all equal numbers;
additionally, the sudoku can be turned or mirrored;
this will produce `9! * 4 * 2 * 2 = 5806080` variations out of one.
There are furthermore some known tricks to exchange
single numbers, resulting to some 10 millions of riddles.

A human will probably not detect the similarity,
but the necessary logical steps are always the same.
This might at the beginning lead to the illusion of an improvement
of skills but in the long term be frustratingly boring.
<br>

This approach builds (primarily) difficult sudokus
in reasonable time from scratch; the underlying idea is not
algorithmic but mathematical.

## How it works

Instead of trying all positions in a completely randomised order,
a (shuffled) 3x3 square is used at first, than an adjacent
other square, and so on.
This leads to some amazing results:
- In the solved sudoku, all possible configurations may appear
- All these configurations appear with (almost) equal probability
- In the unsolved sudoku, all possible configurations may appear
- These configurations do **not** appear with equal probability,
but exactly that was the intention:
Configurations with less remaining numbers (i.e. difficult ones)
are much more presumable.
- Creating solved as unsolved sudoku usually takes very few steps.

In the astronomically unlikely event of the need of many steps
the algorithm stops at some point.

&nbsp;

The branches from **Step1** to **Step8** explain generating a sudoku in general
as well as this approach in particular.

&nbsp;

In case you are not interested in algorithms at all and just want to play:  
Don't forget to set constant `SHOW_SOLVED` to `0`

Enjoy!
