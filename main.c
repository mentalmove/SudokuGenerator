//
//  main.c
//  SudokuGenerator
//
//  Malte Pagel
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>


#define SMALL_LINE 3
#define LINE 9
#define TOTAL 81

#define LIMIT 16777216

#define SHOW_SOLVED 1


struct dimensions_collection {
	int row;
	int column;
	int small_square;
};


int indices[TOTAL];
int riddle[TOTAL];
int solved[TOTAL];
int unsolved[TOTAL];
int tries_to_set = 0;
int taking_back;
int global_unset_count = 0;


struct dimensions_collection get_collection(int);
int contains_element(int*, int, int);
void get_horizontal(int, int*);
void get_vertical(int, int*);
void get_square(int, int*);
int set_values(int, int);
void take_back(int);

int show_solution(int*);


int show_solution (int* solution) {
	
	int i;
	int counter = 0;
	
	printf( " -----------------------------------\n" );
	
	for ( i = 0; i < TOTAL; i++ ) {
		if ( i % LINE == 0 )
			printf( "|" );
		
		if ( solution[i] ) {
			printf( " %d ", solution[i]);
			counter++;
		}
		else
			printf( "   ");
		
		if ( i % LINE == (LINE - 1) ) {
			printf( "|\n" );
			if ( i != (TOTAL - 1) ) {
				if ( i % (SMALL_LINE * LINE) == (SMALL_LINE * LINE - 1) )
					printf( "|-----------+-----------+-----------|\n" );
				else
					printf( "|- - - - - -|- - - - - -|- - - - - -|\n" );
			}
		}
		else {
			if ( i % SMALL_LINE == (SMALL_LINE - 1) )
				printf( "|");
			else
				printf( ":" );
		}
	}
	
	printf( " -----------------------------------" );
	
	return counter;
}


/**
 * Takes a position inside the large square and returns
 *		- the row number
 *		- the column number
 *		- the small square number
 * where this position is situated in
 */
struct dimensions_collection get_collection (int index) {
	struct dimensions_collection ret;
	
	ret.row = (int) (index / LINE);
	ret.column = index % LINE;
	ret.small_square = SMALL_LINE * (int) (ret.row / SMALL_LINE) + (int) (ret.column / SMALL_LINE);
	
	return ret;
}

/**
 * Is 'the_element' in 'the_array'?
 */
int contains_element (int* the_array, int the_element, int length) {
	for ( int i = 0; i < length; i++ )
		if ( the_array[i] == the_element )
			return 1;
	return 0;
}

/**
 * Sets all members of row 'row'
 */
void get_horizontal (int row, int* ret) {
	int j = 0;
	for ( int i = (row * LINE); i < (row * LINE) + LINE; i++ )
		ret[j++] = riddle[i];
}
/**
 * Sets all members of column 'col'
 */
void get_vertical (int col, int* ret) {
	int j = 0;
	for ( int i = col; i < TOTAL; i += LINE )
		ret[j++] = riddle[i];
}
/**
 * Sets all members of small square 'which'
 */
void get_square (int which, int* ret) {
	for ( int i = 0; i < SMALL_LINE; i++ )
		for ( int j = 0; j < SMALL_LINE; j++ )
			ret[SMALL_LINE * i + j] = riddle[LINE * i + which * SMALL_LINE + j + ((int) (which / SMALL_LINE) * (SMALL_LINE - 1) * LINE)];
}

/**
 * Recursive function:
 * Try for each position the numbers from 1 to LINE
 *      (except 'forbidden_number' if given).
 * If all numbers collide with already set numbers, move is bad.
 * If a number doesn't collide with already set numbers,
 *	- move is bad if next move collides with the already set numbers
 *              (including actual one)
 *	- move is good if it's the last one
 */
int set_values (int index, int forbidden_number) {
	
	if ( taking_back && tries_to_set > (2 * LIMIT) )
		return 1;
		
	int real_index = indices[index];
	struct dimensions_collection blocks = get_collection(real_index);
	int elements[LINE];
	
	for ( int i = 1; i <= LINE; i++ ) {
		if ( forbidden_number && i == forbidden_number )
			continue;
		
		tries_to_set++;
		
		get_horizontal(blocks.row, elements);
		if ( contains_element(elements, i, LINE) )
			continue;
		
		get_vertical(blocks.column, elements);
		if ( contains_element(elements, i, LINE) )
			continue;
		
		get_square(blocks.small_square, elements);
		if ( contains_element(elements, i, LINE) )
			continue;
		
		riddle[real_index] = i;
		
		if ( index == (TOTAL - 1) || set_values((index + 1), 0) )
			return 1;
	}
	
	riddle[real_index] = 0;
	
	return 0;
}

/**
 * Some steps to hide unnecessary numbers:
 *	a) Define last piece as 'special piece'
 *	b) Remember this piece's value
 *	c) Try to create riddle from this position on,
 *          but forbid the value of the special piece
 *	d)	I)  If operation fails, define the piece before the special piece
 *          as 'special piece' and continue with b)
 *		II) If operation is possible, reset 'special piece'
 *			and put it to start of list
 *	e) Stop if all pieces are tried or calculation limit is reached
 */
void take_back (int unset_count) {
	
	global_unset_count++;
	
	int i;
	
	int tmp = riddle[indices[TOTAL - unset_count]];
	int redundant = set_values((TOTAL - unset_count), tmp);
	
	if ( !redundant ) {
		unsolved[indices[TOTAL - unset_count]] = 0;
		take_back(++unset_count);
	}
	else {
		riddle[indices[TOTAL - unset_count]] = tmp;
		for ( i = 1; i < unset_count; i++ )
			riddle[indices[TOTAL - unset_count + i]] = 0;
		
		for ( i = (TOTAL - unset_count); i > 0; i-- )
			indices[i] = indices[i - 1];
		indices[0] = tmp;
		
		if ( global_unset_count < TOTAL && tries_to_set < LIMIT )
			take_back(unset_count);
	}
}


int main (int argc, const char * argv[]) {
	
	int i, j, random, small_rows, small_cols, tmp, redundant;
	int multi_raw[LINE][LINE];
	
	
	time_t t;
	time(&t);
	srand((unsigned int) t);
	
	
	
	/**
	 * Initialization:
	 * Fields are set to 0 ( i.e. we dont' know the number yet)
	 */
	for ( i = 0; i < TOTAL; i++ )
		riddle[i] = 0;
	
	/**
	 * Second initialization:
	 * LINE times numbers from 0 to (LINE - 1),
	 * i.e. every square
	 */
	int big_rows_array[] = {0, 1, 2};
	int big_cols_array[] = {0, 1, 2};
	random = rand() % 4;
	switch (random) {
		case 1:
			big_rows_array[0] = 2;
			big_rows_array[1] = 1;
			big_rows_array[2] = 0;
		break;
		case 2:
			big_cols_array[0] = 2;
			big_cols_array[1] = 1;
			big_cols_array[2] = 0;
		break;
		case 3:
			big_rows_array[0] = 2;
			big_rows_array[1] = 1;
			big_rows_array[2] = 0;
			big_cols_array[0] = 2;
			big_cols_array[1] = 1;
			big_cols_array[2] = 0;
	}
	int big_rows, big_cols, big_rows_index, big_cols_index, start_value;
	i = 0;
	j = 0;
	for ( big_rows_index = 0; big_rows_index < SMALL_LINE; big_rows_index++ ) {
		big_rows = big_rows_array[big_rows_index];
		for ( big_cols_index = 0; big_cols_index < SMALL_LINE; big_cols_index++ ) {
			big_cols = big_cols_array[big_cols_index];
			start_value = big_rows * LINE * SMALL_LINE + (big_cols * SMALL_LINE);
			for ( small_rows = 0; small_rows < SMALL_LINE; small_rows++ )
				for ( small_cols = 0; small_cols < SMALL_LINE; small_cols++ )
					multi_raw[i][j++] = small_rows * LINE + small_cols + start_value;
			i++;
			j = 0;
		}
	}
	
	
	/**
	 * Randomization for every element of multi_raw.
	 * Suffle only inside squares
	 */
	for ( i = 0; i < LINE; i++ ) {
		for ( j = 0; j < LINE; j++ ) {
			random = rand() % LINE;
			if ( j == random )
				continue;
			tmp = multi_raw[i][j];
			multi_raw[i][j] = multi_raw[i][random];
			multi_raw[i][random] = tmp;
		}
	}
	
	/**
	 * Linearization
	 */
	for ( i = 0; i < LINE; i++ )
		for ( j = 0; j < LINE; j++ )
			indices[i * LINE + j] = multi_raw[i][j];
	
	
	/**
	 * Setting numbers, start with the first one.
	 * Variable 'redundant' is needed only for formal reasons
	 */
	taking_back = 0;
	redundant = set_values(0, 0);
	
	
	memcpy(solved, riddle, (TOTAL * sizeof(int)));
	memcpy(unsolved, riddle, (TOTAL * sizeof(int)));
	
	
	/**
	 * Exchanging some (few) indices for more randomized game
	 */
	int random2;
	for ( i = (LINE - 1); i > 0; i-- ) {
		for ( j = 0; j < (int) (sqrt(i)); j++ ) {
			
			if ( !(rand() % ((int) (i * sqrt(i)))) || !(LINE - j) )
				continue;
			
			random = i * LINE + (int) (rand() % (LINE - j));
			random2 = rand() % TOTAL;
			
			if ( random == random2 )
				continue;
			
			tmp = indices[random];
			indices[random] = indices[random2];
			indices[random2] = tmp;
		}
	}
	
	
	tries_to_set = 0;
	taking_back = 1;
	take_back(1);
	
	
	if ( SHOW_SOLVED ) {
		printf( "\n\n" );
		redundant = show_solution(solved);
		printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
	}
	else
		printf( "\n\n\n\n" );
	
	int counter = show_solution(unsolved);
	printf( "\t *** %d numbers left *** \n", counter );
	
	
	return 0;
}
