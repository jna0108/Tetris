#pragma once

#include "Board.h"
#include "Tetromino.h"
#include <time.h>

/* 
	Draws the board and pieces
		Pass the renderer in from main function to draw
	Generate random pieces
	Clears the screen
	Updates the screen
	Takes care of key presses
	Makes pieces move down
*/

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
	const int nRot = 3, nX = 12, nY = 2;	// next piece's fields are always the same

	void initGame();
	void drawBoard(SDL_Renderer* renderer);
	void drawMino(SDL_Renderer* renderer, int mino, int rotation, int x, int y);
};