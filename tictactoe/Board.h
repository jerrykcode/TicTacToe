#pragma once
typedef char ** Board;
typedef char ChessType;
#define X 'X'
#define O 'O'
#define EMPTY '-'
#define REVERSE_CHESS_TYPE(type) (type == EMPTY ? EMPTY : (type == X ? O : X))
#define NROWS 3
#define NCOLS 3

#define NRESULTS 3
typedef enum {
	WIN,
	LOSE,
	DRAW,
} RESULT;

struct Position {
	Position(int row, int col) : row(row), col(col) {}
	Position() {}
	int row;
	int col;
};
