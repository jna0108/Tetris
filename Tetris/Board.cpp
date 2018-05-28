#include "stdafx.h"
#include "Board.h"

Board::Board(Tetromino *tetrominoes, int boardOriginX, int boardOriginY, int dim)
{
	minoes = tetrominoes;
	origX = boardOriginX;
	origY = boardOriginY;
	block_dim = dim;
	initBoard();
}

int Board::getBlock(int x, int y)
{
	return board[x][y];
}

void Board::initBoard()
{
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			board[row][col] = 0;
		}
	}
}

// Check if space is free
bool Board::isFreeSpace(int x, int y)
{
	return (board[x][y] == 0);
}

// (x, y) is top left of 5x5 array
bool Board::isValidMove(int x, int y, int mino, int rotation) {
	for (int i = y, row = 0; i < y + MINO_DIM; row++, i++) {
		for (int j = x, col = 0; j < x + MINO_DIM; col++, j++) {
			int block = minoes->getMino(mino, rotation, row, col);
			if (block > 0) {
				// check for collision with walls
				if (j < 0 || j > width - 1 || i >= height ) {
					return false;
				}

				// check for collision with board
				if (!isFreeSpace(i, j)) {
					return false;
				}
			}
		}
	}
	return true;
}

void Board::addToBoard(int x, int y, int mino, int rotation)
{
	for (int i = y, row = 0; i < y + MINO_DIM; row++, i++) {
		for (int j = x, col = 0; j < x + MINO_DIM; col++, j++) {
			uint8_t pixel = minoes->getMino(mino, rotation, row, col);
			if (pixel > 0) {
				board[i][j] = pixel;
			}
		}
	}
}

// move lines above row downwards
void Board::deleteLine(int row)
{
	for (int i = row; i > 0; i--) {
		for (int j = 0; j < width; j++) {
			board[i][j] = board[i - 1][j];
		}
	}
	
	// make sure top row is clear
	for (int j = 0; j < width; j++) {
		board[0][j] = 0;
	}


}

// detect lines that are full in
// m * n time... is there a faster way?
void Board::detectLines()
{
	for (int line = height - 1; line >= 0; line--) {
		int j = 0;
		while (j < width) {
			if (board[line][j] == 0) {
				break;
			}
			j++;
		}
		if (j == width) {
			deleteLine(line);
			line++;
		}
	}
}

// Checks top row for game over
bool Board::isGameOver()
{
	for (int j = 0; j < width; j++) {
		if (board[0][j] > 0) {
			return true;
		}
	}
	return false;
}