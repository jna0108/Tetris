#pragma once

#include "Tetromino.h"

/*
	pixels pixels pixels
*/

#define HEIGHT 20							// height of board in blocks (1 extra row at top to check for death)
#define WIDTH 10							// width of board in blocks
#define MINO_DIM 5							// each mino has 5 blocks

class Board
{
public:
	Board(Tetromino *tetrominoes, int boardOriginX, int boardOriginY, int dim);
	bool isFreeSpace(int x, int y);
	bool isValidMove(int x, int y, int mino, int rotation);
	void addToBoard(int x, int y, int mino, int rotation);
	void detectLines();
	void deleteLine(int row);
	bool isGameOver();

	int origX, origY, block_dim;
	int height = 20, width = 10;
private:
	bool board[HEIGHT][WIDTH];
	Tetromino *minoes;
	void initBoard();
};

