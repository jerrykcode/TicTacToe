#pragma once
typedef char ** Board;
#define X 'X'
#define O 'O'
#define EMPTY '-'
#define NROWS 3
#define NCOLS 3

struct Position {
	Position(int row, int col) : row(row), col(col) {}
	Position() {}
	int row;
	int col;
};
