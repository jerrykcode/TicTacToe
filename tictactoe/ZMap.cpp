#include "ZMap.h"

ZMap::ZMap()
{
	XBoard = create2DArrayWithRandom();
	OBoard = create2DArrayWithRandom();
	EmptyBoard = create2DArrayWithRandom();
}

ZMap::~ZMap()
{
	free2DArray(XBoard);
	free2DArray(OBoard);
	free2DArray(EmptyBoard);
}

int ** ZMap::create2DArrayWithRandom()
{
	int ** arr = new int*[NROWS];
	for (int i = 0; i < NROWS; i++) {
		arr[i] = new int[NCOLS];
		for (int j = 0; j < NCOLS; j++)
			arr[i][j] = rand();
	}
	return arr;
}

void ZMap::free2DArray(int ** arr)
{
	for (int i = 0; i < NROWS; i++)
		free(arr[i]);
	free(arr);
}

void ZMap::insert(Board board, BestResult bResult)
{
	int key = getKey(board);
	map_[key] = bResult;
}

bool ZMap::hasKey(Board board)
{
	int key = getKey(board);
	return map_.find(key) != map_.end();
}

BestResult ZMap::getValue(Board board)
{
	int key = getKey(board);
	return map_[key];
}

int ZMap::getKey(Board board)
{
	int res = 0;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++) {
			int zcode;
			switch (board[row][col]) {
			case X: zcode = XBoard[row][col]; break;
			case O: zcode = OBoard[row][col]; break;
			case EMPTY: zcode = EmptyBoard[row][col]; break;
			}
			res ^= zcode;
		}
	return res;
}