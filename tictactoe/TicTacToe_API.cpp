#ifdef TICTACTOE_EXPORTS
#define TICTACTOE_API __declspec(dllexport)
#else 
#define TICTACTOE_API __declspec(dllimport)
#endif

#include "TicTacToe.h"

#ifdef __cplusplus
extern "C" {
#endif

	TicTacToe tictactoe;

	TICTACTOE_API void init(char chessType) {
		if (chessType == 'X') {
			tictactoe = *(new TicTacToe(X));
		}
		else {
			tictactoe = *(new TicTacToe(O));
		}
	}

	TICTACTOE_API bool isValid(int row, int col) {
		return tictactoe.isValid(row, col);
	}

	TICTACTOE_API void human(int row, int col) {
		tictactoe.human(row, col);
	}

	TICTACTOE_API void computer() {
		tictactoe.computer();
	}
	
	TICTACTOE_API int getComputerRow() {
		return tictactoe.getComputerRow();
	}

	TICTACTOE_API int getComputerCol() {
		return tictactoe.getComputerCol();
	}

	TICTACTOE_API void updateTurnAfterComputerTurn() {
		tictactoe.updateTurnAfterComputerTurn();
	}

#ifdef __cplusplus
}
#endif