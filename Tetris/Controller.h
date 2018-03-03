#pragma once

#include "Board.h"
#include "Tetromino.h"
#include <time.h>

class Controller
{
public:
	Controller(Board* board, Tetromino* minoes);
	void draw(SDL_Renderer* renderer);
	void generatePiece();
	int cMino, cRot, cX, cY;				// current piece
private:
	Board *board;
	Tetromino *minoes;
	int nMino;								// next piece
	const int nRot = 0, nX = 12, nY = 2;	// next piece's fields are always the same

	void initGame();
	void drawBoard(SDL_Renderer* renderer);
	void drawMino(SDL_Renderer* renderer, int mino, int rotation, int x, int y);
};