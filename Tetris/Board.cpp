#include "stdafx.h"
#include "Board.h"


Board::Board(Tetromino *tetrominoes, int boardOriginX, int boardOriginY)
{
	minoes = tetrominoes;
	origX = boardOriginX;
	origY = boardOriginY;
	initBoard();
}

void Board::initBoard()
{
	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			board[row][col] = false;
		}
	}
}

// Check if space is free
bool Board::isFreeSpace(int x, int y)
{
	return !board[x][y];
}

// (x, y) is top left of 5x5 array
bool Board::isValidMove(int x, int y, int mino, int rotation) {
	for (int i = x, row = 0; i < x + MINO_DIM; row++, i++) {
		for (int j = y, col = 0; j < y + MINO_DIM; col++, j++) {
			int block = minoes->getMino(mino, rotation, row, col);

			// check for collision with walls
			if (i < 0 || j < 0 || i > HEIGHT - 1 || j > WIDTH - 1) {
				if (block == 1)
					return false;
			}
			
			// check for collision with board
			if ((block == 1) && isFreeSpace(i, j)) {
				return false;
			}
		}
	}

	return true;
}

void Board::addToBoard(int x, int y, int mino, int rotation)
{
	for (int i = x, row = 0; i < x + MINO_DIM; row++, i++) {
		for (int j = y, col = 0; j < y + MINO_DIM; col++, j++) {
			if (minoes->getMino(mino, rotation, row, col) == 1) {
				board[i][j] = true;
			}
		}
	}
}

// move lines above row downwards
void Board::deleteLine(int row)
{
	for (int i = row; i < HEIGHT - 1; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = board[i+ 1][j];
		}
	}
	
	// make sure top row is clear
	for (int j = 0; j < WIDTH; j++) {
		board[HEIGHT][j] = false;
	}


}

// detect lines that are full in
// m * n time... is there a faster way?
void Board::detectLines()
{
	int j;
	for (int line = 0; line < HEIGHT; line++) {
		j = 0;
		while (j < WIDTH) {
			if (board[line][j] == false) {
				break;
			}
			j++;
		}
		if (j == WIDTH) {
			deleteLine(line);
		}
	}
}


bool Board::isGameOver()
{
	for (int j = 0; j < WIDTH; j++) {
		if (board[HEIGHT][j] == true) {
			return true;
		}
	}
	return false;
}