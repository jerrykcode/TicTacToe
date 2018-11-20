#pragma once
#include "Board.h"
#include "ZMap.h"

typedef enum {
	OK,
	ERROR,
} TICRESULT;

#define MIN_SCORE -1
#define MAX_SCORE 1

typedef Position* PPosition;

class TicTacToe {

public:

	TicTacToe(ChessType humanChessType) 
		: computerChessType(REVERSE_CHESS_TYPE(humanChessType)),
		isComputerTurn(computerChessType == X)
	{
		score[WIN] = MAX_SCORE;
		score[LOSE] = MIN_SCORE;
		score[DRAW] = 0;
		board = new char*[NROWS];
		for (int row = 0; row < NROWS; row++) {
			board[row] = new char[NCOLS];
			for (int col = 0; col < NCOLS; col++) {
				board[row][col] = EMPTY;
			}
		}
	}

	TicTacToe() {}

	~TicTacToe() {
		for (int i = 0; i < NROWS; i++)
			free(board[i]);
		free(board);
	}
	
	bool isValid(int row, int col);
	void human(int row, int col);
	void computer();

	int getComputerRow() {
		return computerRow;
	}

	int getComputerCol() {
		return computerCol;
	}

	void updateTurnAfterComputerTurn();

	bool gameOver(RESULT * pResult);

private:

	TICRESULT addX(int row, int col);
	TICRESULT addO(int row, int col);

	int getBestPosition(ChessType chessType, int preBestScore, PPosition pPosition);

	int computerRow;
	int computerCol;

	bool isComputerTurn;
	ChessType computerChessType;
	int score[NRESULTS];
	Board board;
	ZMap zmap;

};