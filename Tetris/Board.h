#pragma once

#include "Tetromino.h"

/*
	Lots to do in this class:
	1. Detect Collisions (isFreeSpace/isValidMove)
	2. Structure pieces 
	3. Delete lines (deleteline)
	4. Initialize Board (2d array) (initboard)
	5. Change shape of board as pieces fall (addtoboard)
*/

#define HEIGHT 20
#define WIDTH 10
#define MINO_DIM 5

class Board
{
public:
	Board(Tetromino *tetrominoes);
	bool isFreeSpace(int x, int y);
	bool isValidMove(int x, int y, int mino, int rotation);
	void addToBoard(int x, int y, int mino, int rotation);
	void detectLines();
	void deleteLine();
	bool isGameOver();
	virtual ~Board();
private:
	bool board[HEIGHT][WIDTH];
	Tetromino *minoes;
	void initBoard();
};

