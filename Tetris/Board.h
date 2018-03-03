#pragma once

#include "Tetromino.h"

/*
	pixels pixels pixels
*/

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

	int origX, origY;				// top left corner of board
	int block_dim;					// side length of block in pixels	
	int height = 20, width = 10;	// height and width in blocks
private:
	bool board[20][10];
	int mino_size = 5;
	Tetromino *minoes;
	void initBoard();
};

