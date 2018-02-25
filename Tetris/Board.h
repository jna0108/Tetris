#pragma once

#include "Tetromino.h"

/*
	pixels pixels pixels
*/

#define HEIGHT 21							// height of board (1 extra row at top to check for death)
#define WIDTH 10							// width of board
#define BLOCK_DIM 10						// each block of a mino is 10 pixels wide
#define MINO_DIM 5							// each mino has 5 blocks

class Board
{
public:
	Board(Tetromino *tetrominoes, int boardOriginX, int boardOriginY);
	bool isFreeSpace(int x, int y);
	bool isValidMove(int x, int y, int mino, int rotation);
	void addToBoard(int x, int y, int mino, int rotation);
	void detectLines();
	void deleteLine(int row);
	bool isGameOver();

	int origX, origY;
private:
	bool board[HEIGHT][WIDTH];
	Tetromino *minoes;
	void initBoard();
};

