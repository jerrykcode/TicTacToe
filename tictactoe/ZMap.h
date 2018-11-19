#pragma once
#include "Board.h"
#include <map>
#include <random>
using namespace std;

struct BestResult {
	BestResult(Position pos, int score) : pos(pos), score(score) {}
	BestResult() {}
	Position pos;
	int score;
};

class ZMap {
public:
	ZMap();
	~ZMap();

	void insert(Board board, BestResult bResult);
	bool hasKey(Board board);
	BestResult getValue(Board board);

private:

	int ** create2DArrayWithRandom();
	void free2DArray(int **arr);

	int getKey(Board board);

	map<int, BestResult> map_;

	int **XBoard;
	int **OBoard;
	int **EmptyBoard;

	default_random_engine rand;
};
