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
	Controller(Board *board, Tetromino *minoes);
	void draw();
	void generatePiece();
private:
	Board *board;
	Tetromino *minoes;
	int currMino;

	void initGame();
	void drawBoard();
	void drawMino();
};

