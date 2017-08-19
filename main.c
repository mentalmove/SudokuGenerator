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
uint set_values(uint, uint);
void take_back(uint);


uint SMALL_LINE, LINE, TOTAL;
uint* sudoku;
uint* unsolved;

uint tries_to_set = 0;
uint global_unset_count = 0;


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


uint set_values (uint index, uint forbidden_number) {
	
	uint elements[9];												// taking the larger size for both
	struct dimensions_collection blocks = get_collection(index);
	
	for ( uint i = 1; i <= LINE; i++ ) {
		
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
		
		sudoku[index] = i;
		
		if ( index == (TOTAL - 1) || set_values((index + 1), 0) )
			return 1;
	}
	
	sudoku[index] = 0;
	
	return 0;
}

void take_back (uint unset_count) {
	
	global_unset_count++;
	
	uint i;
	
	uint tmp = sudoku[TOTAL - unset_count];
	uint redundant = set_values((TOTAL - unset_count), tmp);
	
	if ( !redundant ) {
		unsolved[TOTAL - unset_count] = 0;
		take_back(++unset_count);
	}
	else {
		sudoku[TOTAL - unset_count] = tmp;
		for ( i = 1; i < unset_count; i++ )
			sudoku[TOTAL - unset_count + i] = 0;
		
		if ( global_unset_count < TOTAL )
			take_back(unset_count);
	}
}


int main (int argc, const char* argv[]) {
	
	set_quasi_constants(2, &SMALL_LINE, &LINE, &TOTAL);
	sudoku = calloc(TOTAL, sizeof(uint));
	unsolved = calloc(TOTAL, sizeof(uint));;
	uint redundant = set_values(0, 0);
	show_solution(sudoku);
	printf( " \t %d tries needed", tries_to_set );
	
	printf( "\n" );
	
	memcpy(unsolved, sudoku, (TOTAL * sizeof(int)));
	tries_to_set = 0;
	take_back(1);
	show_solution(unsolved);
	printf( " \t %d additional", tries_to_set );

	
	printf( "\n\n" );
	
	
	set_quasi_constants(3, &SMALL_LINE, &LINE, &TOTAL);
	sudoku = realloc(sudoku, TOTAL * sizeof(uint));
	unsolved = realloc(sudoku, TOTAL * sizeof(uint));
	memset(sudoku, 0, TOTAL);
	tries_to_set = 0;
	redundant = set_values(0, 0);
	show_solution(sudoku);
	printf( " \t %d tries needed", tries_to_set );
	
	printf( "\n" );
	
	memcpy(unsolved, sudoku, (TOTAL * sizeof(int)));
	tries_to_set = 0;
	global_unset_count = 0;
	take_back(1);
	show_solution(unsolved);
	printf( " \t %d additional", tries_to_set );
	
	
	printf( "\n\n" );
	
	
	free(sudoku);
	
	
	return 0;
}
