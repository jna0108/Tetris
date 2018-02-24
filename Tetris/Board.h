#pragma once

#include "Tetromino.h"

/*
	pixels pixels pixels
*/

#define HEIGHT 21
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
	void deleteLine(int row);
	bool isGameOver();
private:
	bool board[HEIGHT][WIDTH];
	Tetromino *minoes;
	void initBoard();
};

