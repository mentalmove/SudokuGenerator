//
//  main.c
//  SudokuGenerator
//
//  Malte Pagel
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef unsigned int uint;


void border_line(void);
void solid_line(void);
void dotted_line(void);
void show_solution (uint*);
void set_quasi_constants (uint, uint*, uint*, uint*);
void get_horizontal(uint, uint*);
void get_vertical(uint, uint*);
void get_square(uint, uint*);


uint sudoku4x4[] = {
	1, 2, 4, 3,
	4, 3, 1, 2,
	2, 4, 3, 1,
	3, 1, 2, 4
};
uint sudoku9x9[] = {
	1, 6, 7, 2, 9, 5, 8, 4, 3,
	5, 8, 4, 3, 7, 6, 1, 2, 9,
	2, 9, 3, 1, 4, 8, 6, 7, 5,
	4, 3, 1, 6, 8, 2, 9, 5, 7,
	7, 2, 6, 9, 5, 3, 4, 8, 1,
	9, 5, 8, 7, 1, 4, 3, 6, 2,
	8, 1, 9, 4, 2, 7, 5, 3, 6,
	3, 4, 2, 5, 6, 1, 7, 9, 8,
	6, 7, 5, 8, 3, 9, 2, 1, 4
};


uint SMALL_LINE, LINE, TOTAL;


void border_line () {
	printf( " " );
	for ( uint i = 0; i < 4 * pow(SMALL_LINE, 2) - 1; i++ )
		printf( "-" );
}
void solid_line () {
	printf( "|" );
	for ( uint i = 0; i < SMALL_LINE; i++ ) {
		printf( "---" );
		for ( uint j = 0; j < SMALL_LINE - 1; j++ ) {
			printf( "----" );
		}
		if ( i < SMALL_LINE - 1 )
			printf( "+" );
	}
	printf( "|\n" );
}
void dotted_line () {
	printf( "|" );
	for ( uint i = 0; i < SMALL_LINE; i++ ) {
		printf( "- -" );
		for ( uint j = 0; j < SMALL_LINE - 1; j++ ) {
			printf( " - -" );
		}
		printf( "|" );
	}
	printf( "\n" );
}
void show_solution (uint* solution) {
	
	uint i;
	uint counter = 0;
	
	border_line();
	printf( "\n" );
	
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
					solid_line();
				else
					dotted_line();
			}
		}
		else {
			if ( i % SMALL_LINE == (SMALL_LINE - 1) )
				printf( "|");
			else
				printf( ":" );
		}
	}
	
	border_line();
}

void set_quasi_constants (uint small_line_value, uint* small_line, uint* line, uint* total) {
	*small_line = small_line_value;
	*line = pow(small_line_value, 2);
	*total = pow(small_line_value, 4);
}

void get_horizontal (uint row, uint* sudoku) {
	printf( "Row %d contains ", row );
	for ( int i = (row * LINE); i < (row * LINE) + LINE; i++ ) {
		if ( i % LINE )
			printf( ", " );
		printf( "%d", sudoku[i] );
	}
	printf( "\n" );
}
void get_vertical (uint col, uint* sudoku) {
	printf( "Column %d contains ", col );
	for ( int i = col; i < TOTAL; i += LINE ) {
		if ( i >= LINE )
			printf( ", " );
		printf( "%d", sudoku[i] );
	}
	printf( "\n" );
}
void get_square (uint which, uint* sudoku) {
	printf( "Square %d contains ", which );
	for ( int i = 0; i < SMALL_LINE; i++ )
		for ( int j = 0; j < SMALL_LINE; j++ ) {
			if ( i || j )
				printf( ", " );
			printf( "%d", sudoku[LINE * i + which * SMALL_LINE + j + ((int) (which / SMALL_LINE) * (SMALL_LINE - 1) * LINE)] );
		}
	printf( "\n" );
}


int main (int argc, const char* argv[]) {
	
	uint i;
	
	set_quasi_constants(2, &SMALL_LINE, &LINE, &TOTAL);
	for ( i = 0; i < LINE; i++ )
		get_horizontal(i, sudoku4x4);
	for ( i = 0; i < LINE; i++ )
		get_vertical(i, sudoku4x4);
	for ( i = 0; i < LINE; i++ )
		get_square(i, sudoku4x4);
	show_solution(sudoku4x4);
	
	printf( "\n\n" );

	set_quasi_constants(3, &SMALL_LINE, &LINE, &TOTAL);
	for ( i = 0; i < LINE; i++ )
		get_horizontal(i, sudoku9x9);
	for ( i = 0; i < LINE; i++ )
		get_vertical(i, sudoku9x9);
	for ( i = 0; i < LINE; i++ )
		get_square(i, sudoku9x9);
	show_solution(sudoku9x9);
	
	printf( "\n\n" );
	
	
	return 0;
}
