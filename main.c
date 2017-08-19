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

struct dimensions_collection {
	int row;
	int column;
	int small_square;
};


void set_quasi_constants (uint, uint*, uint*, uint*);
struct dimensions_collection get_collection(uint);


uint SMALL_LINE, LINE, TOTAL;


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


int main (int argc, const char* argv[]) {
	
	uint i;
	struct dimensions_collection blocks;
	
	set_quasi_constants(2, &SMALL_LINE, &LINE, &TOTAL);
	for ( i = 0; i < TOTAL; i++ ) {
		blocks = get_collection(i);
		printf( "Index %d is in row %d, column %d, square %d\n", i, blocks.row, blocks.column, blocks.small_square );
	}
	
	printf( "\n\n" );
	
	set_quasi_constants(3, &SMALL_LINE, &LINE, &TOTAL);
	for ( i = 0; i < TOTAL; i++ ) {
		blocks = get_collection(i);
		printf( "Index %d is in row %d, column %d, square %d\n", i, blocks.row, blocks.column, blocks.small_square );
	}

	printf( "\n\n" );
	
	
	return 0;
}
