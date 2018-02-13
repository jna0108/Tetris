#include "stdafx.h"
#include "Board.h"


Board::Board(Tetromino *tetrominoes)
{
	minoes = tetrominoes;
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

// 
bool Board::isFreeSpace(int x, int y)
{
	return !board[x][y];
}

// (x, y) is bottom right of 5x5 array
bool Board::isValidMove(int x, int y, int mino, int rotation)
{
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

// detect lines that are full
// m * n time... is there a faster way?
void Board::detectLines()
{

}

// move upper lines down?
void Board::deleteLine(int row)
{
	for (int i = 0; i < WIDTH; i++) {
		board[row][i] = 0;
	}
}

bool Board::isGameOver()
{
	return false;
}

Board::~Board()
{
}


