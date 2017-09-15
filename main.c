//
//  main.c
//  SudokuGenerator
//
//  Malte Pagel
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define PATIENCE 0			// might take weeks, maybe years


typedef unsigned int uint;

struct dimensions_collection {
	int row;
	int column;
	int small_square;
};


void border_line(void);
void solid_line(void);
void dotted_line(void);
void show_solution (uint*);
void set_quasi_constants (uint, uint*, uint*, uint*);
struct dimensions_collection get_collection(uint);
void get_horizontal(uint, uint*);
void get_vertical(uint, uint*);
void get_square(uint, uint*);
uint contains_element(uint*, uint, uint);
uint set_values(uint);


uint SMALL_LINE, LINE, TOTAL;
uint* sudoku;
uint* indices;

long double tries_to_set = 0;


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

struct dimensions_collection get_collection (uint index) {
	struct dimensions_collection ret;
	
	ret.row = (uint) (index / LINE);
	ret.column = index % LINE;
	ret.small_square = SMALL_LINE * (int) (ret.row / SMALL_LINE) + (int) (ret.column / SMALL_LINE);
	
	return ret;
}

void get_horizontal (uint row, uint* ret) {
	uint j = 0;
	for ( uint i = (row * LINE); i < (row * LINE) + LINE; i++ )
		ret[j++] = sudoku[i];
}
void get_vertical (uint col, uint* ret) {
	uint j = 0;
	for ( uint i = col; i < TOTAL; i += LINE )
		ret[j++] = sudoku[i];
}
void get_square (uint which, uint* ret) {
	for ( uint i = 0; i < SMALL_LINE; i++ )
		for ( uint j = 0; j < SMALL_LINE; j++ )
			ret[SMALL_LINE * i + j] = sudoku[LINE * i + which * SMALL_LINE + j + ((uint) (which / SMALL_LINE) * (SMALL_LINE - 1) * LINE)];
}

uint contains_element (uint* the_array, uint the_element, uint length) {
	for ( uint i = 0; i < length; i++ )
		if ( the_array[i] == the_element )
			return 1;
	return 0;
}


uint set_values (uint index) {
	
	uint real_index = indices[index];
	uint elements[9];												// taking the larger size for both
	struct dimensions_collection blocks = get_collection(real_index);
	
	for ( uint i = 1; i <= LINE; i++ ) {
		
		tries_to_set++;
		
		if ( (uint) tries_to_set % 16384 == 0 ) {
			show_solution(sudoku);
			printf( " \t %.Lf\n", tries_to_set );
		}
		
		get_horizontal(blocks.row, elements);
		if ( contains_element(elements, i, LINE) )
			continue;
		
		get_vertical(blocks.column, elements);
		if ( contains_element(elements, i, LINE) )
			continue;
		
		get_square(blocks.small_square, elements);
		if ( contains_element(elements, i, LINE) )
			continue;
		
		sudoku[real_index] = i;
		
		if ( index == (TOTAL - 1) || set_values(index + 1) )
			return 1;
	}
	
	sudoku[real_index] = 0;
	
	return 0;
}


int main (int argc, const char* argv[]) {
	
	uint i, determined;
	
	time_t t;
	time(&t);
	srand((unsigned int) t);
	
	
	set_quasi_constants(2, &SMALL_LINE, &LINE, &TOTAL);
	sudoku = calloc(TOTAL, sizeof(uint));
	indices = malloc(TOTAL * sizeof(uint));
	
	indices[0] = 0;
	for ( i = 1; i < TOTAL; i++ )
		indices[i] = (indices[i - 1] + LINE + 1) % TOTAL;
	uint redundant = set_values(0);
	printf( "Easy:\n" );
	show_solution(sudoku);
	printf( " \t %d tries needed", (uint) tries_to_set );
	
	printf( "\n" );

	for ( i = 0; i < TOTAL; i++ ) {
		sudoku[i] = 0;
		determined = (2 * i) % TOTAL;
		if ( i >= (TOTAL / 2) )
			determined++;
		indices[i] = determined;
	}
	tries_to_set = 0;
	redundant = set_values(0);
	printf( "Difficult:\n" );
	show_solution(sudoku);
	printf( " \t %d tries needed", (uint) tries_to_set );

	
	printf( "\n\n" );
	
	
	set_quasi_constants(3, &SMALL_LINE, &LINE, &TOTAL);
	sudoku = realloc(sudoku, TOTAL * sizeof(uint));
	indices = realloc(indices, TOTAL * sizeof(uint));
	indices[0] = 0;
	sudoku[0] = 0;
	for ( i = 1; i < TOTAL; i++ ) {
		sudoku[i] = 0;
		indices[i] = (indices[i - 1] + LINE + 1) % TOTAL;
	}
	tries_to_set = 0;
	redundant = set_values(0);
	printf( "Easy:\n" );
	show_solution(sudoku);
	printf( " \t %d tries needed", (uint) tries_to_set );
	
	
	if ( PATIENCE ) {
		for ( i = 0; i < TOTAL; i++ ) {
			sudoku[i] = 0;
			determined = (2 * i) % TOTAL;
			indices[i] = determined;
		}
		tries_to_set = 0;
		redundant = set_values(0);
		printf( "Difficult:\n" );
		show_solution(sudoku);
		printf( " \t %Lf tries needed", tries_to_set );
	}
	
	printf( "\n\n" );
	
	
	free(sudoku);
	free(indices);
	
	
	return 0;
}
