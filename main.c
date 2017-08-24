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
void show_solution(uint*);
void set_quasi_constants(uint, uint*, uint*, uint*);
void fill_rows(uint*);
void fill_cols(uint*);
void fill_small_squares(uint*);


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

void fill_rows (uint* linear) {
	for ( uint i = 0; i < TOTAL; i++ )
		linear[i] = i % LINE + 1;
}
void fill_cols (uint* linear) {
	for ( uint i = 0; i < TOTAL; i++ )
		linear[i] = i / LINE + 1;
}
void fill_small_squares (uint* linear) {
	for ( uint i = 0; i < TOTAL; i++ )
		linear[i] = (i / LINE) % SMALL_LINE * SMALL_LINE + i % SMALL_LINE + 1;
}


int main (int argc, const char* argv[]) {
	
	uint * sudoku;
	
	
	set_quasi_constants(2, &SMALL_LINE, &LINE, &TOTAL);
	sudoku = malloc(TOTAL * sizeof(uint));
	fill_rows(sudoku);
	show_solution(sudoku);
	printf( " \t correct rows" );
	printf( "\n\n" );
	fill_cols(sudoku);
	show_solution(sudoku);
	printf( " \t correct columns" );
	printf( "\n\n" );
	fill_small_squares(sudoku);
	show_solution(sudoku);
	printf( " \t correct small squares" );
	
	printf( "\n\n\n" );
	
	set_quasi_constants(3, &SMALL_LINE, &LINE, &TOTAL);
	sudoku = realloc(sudoku, TOTAL * sizeof(uint));
	fill_rows(sudoku);
	show_solution(sudoku);
	printf( " \t correct rows" );
	printf( "\n\n" );
	fill_cols(sudoku);
	show_solution(sudoku);
	printf( " \t correct columns" );
	printf( "\n\n" );
	fill_small_squares(sudoku);
	show_solution(sudoku);
	printf( " \t correct small squares" );
	
	printf( "\n\n" );
	
	
	free(sudoku);
	
	
	return 0;
}
