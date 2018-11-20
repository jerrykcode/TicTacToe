#include "TicTacToe.h"
#define NO_ALPHA_BTEA (MIN_SCORE - 1)
typedef enum {
	SEARCH_MAX,
	SEARCH_MIN,
} SearchType;

TICRESULT TicTacToe::addX(int row, int col)
{
	if (board[row][col] != EMPTY) return ERROR;
	board[row][col] = X;
	return OK;
}

TICRESULT TicTacToe::addO(int row, int col)
{
	if (board[row][col] != EMPTY) return ERROR;
	board[row][col] = O;
	return OK;
}

bool TicTacToe::isValid(int row, int col)
{
	return (!isComputerTurn) && board[row][col] == EMPTY;
}

void TicTacToe::human(int row, int col)
{
	if (computerChessType == X) {
		addO(row, col);
	}
	else {
		addX(row, col);
	}
	isComputerTurn = true;
}

void TicTacToe::computer()
{
	PPosition pPosition = (PPosition)malloc(sizeof(Position));
	getBestPosition(computerChessType, NO_ALPHA_BTEA, pPosition);
	computerRow = pPosition->row;
	computerCol = pPosition->col;
	if (computerChessType == X) {
		addX(computerRow, computerCol);
	}
	else {
		addO(computerRow, computerCol);
	}
	delete pPosition;
}

void TicTacToe::updateTurnAfterComputerTurn()
{
	isComputerTurn = false;
}

int TicTacToe::getBestPosition(ChessType chessType, int preBestScore, PPosition pPosition)
{
	if (zmap.hasKey(board)) {
		BestResult bestResult = zmap.getValue(board);
		*pPosition = bestResult.pos;
		return bestResult.score;
	}	
	SearchType searchType = chessType == computerChessType ? SEARCH_MAX : SEARCH_MIN;
	int bestScore = searchType == SEARCH_MAX ? (MIN_SCORE - 1) : (MAX_SCORE + 1);
	int bestRow, bestCol;
	bool useAlphaBetaPurning = false;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++) {
			if (board[row][col] == EMPTY) {
				board[row][col] = chessType;
				int currentScore;
				RESULT result;
				if (gameOver(&result)) currentScore = score[result];
				currentScore = getBestPosition(REVERSE_CHESS_TYPE(chessType), bestScore, pPosition);
				board[row][col] = EMPTY;
				switch (searchType) {
				case SEARCH_MAX: {
					if (currentScore > bestScore) {
						bestScore = currentScore;
						bestRow = row;
						bestCol = col;
					}
					if (preBestScore != NO_ALPHA_BTEA && currentScore >= preBestScore) {
						return currentScore;
					}
					break;
				}
				case SEARCH_MIN: {
					if (currentScore < bestScore) {
						bestScore = currentScore;
						bestRow = row;
						bestCol = col;
					}
					if (preBestScore != NO_ALPHA_BTEA && currentScore <= preBestScore) {
						return currentScore;
					}
					break;
				}
				}
			}
		}
	//for row
	Position bestPosition(bestRow, bestCol);
	zmap.insert(board, BestResult(bestPosition, bestScore));
	*pPosition = bestPosition;
	return bestScore;
}

bool TicTacToe::gameOver(RESULT * pResult)
{
	//Check rows
	for (int row = 0; row < NROWS; row++) {
		bool flag = true;
		for (int col = 0; col < NCOLS; col++) {
			if (board[row][col] != board[row][0]) {
				flag = false;
				break;
			}
		}
		if (flag) { //If this row consisted by chesses with same type
			(*pResult) = board[row][0] == computerChessType ? WIN : LOSE;
			return true;
		}
	}
	//check columns
	for (int col = 0; col < NCOLS; col++) {
		bool flag = true;
		for (int row = 0; row < NROWS; row++) {
			if (board[row][col] != board[0][col]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			(*pResult) = board[0][col] == computerChessType ? WIN : LOSE;
			return true;
		}
	}
	//check diagnose
	bool flag = true;
	for (int i = 0; i < NROWS; i++)
		if (board[i][i] != board[0][0]) {
			flag = false;
			break;
		}
	if (flag) {
		(*pResult) = board[0][0] == computerChessType ? WIN : LOSE;
		return true;
	}
	flag = true;
	for (int i = 0; i < NROWS; i++)
		if (board[i][NROWS - i - 1] != board[0][NROWS - 0 - 1]) {
			flag = false;
			break;
		}
	if (flag) {
		(*pResult) = board[0][NROWS - 0 - 1] == computerChessType ? WIN : LOSE;
		return true;
	}
	//check draw
	flag = true;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++)
			if (board[row][col] == EMPTY) {
				flag = false;
				break;
			}
	if (flag) {
		(*pResult) = DRAW;
		return true;
	}
	return false;
}