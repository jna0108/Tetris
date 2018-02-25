#include "stdafx.h"
#include "Controller.h"

Controller::Controller(Board* board, Tetromino* minoes)
{
	this->board = board;
	this->minoes = minoes;
	initGame();
}

void Controller::draw(SDL_Renderer* renderer)
{
	drawBoard(renderer);
	drawMino(renderer, cMino, cRot, cX, cY);
}

void Controller::generatePiece()
{
	// Make next piece the current piece
	cMino = nMino;
	cRot = nRot;
	cX = 0;
	cY = 0;

	// Spawn next piece
	nMino = rand() % 7;
}

void Controller::initGame()
{
	// Spawn initial piece
	cMino = rand() % 7; // 0 to 6
	cRot = 0, cX = 0, cY = 0;

	// Spawn initial next piece
	nMino = rand() % 7;
}

void Controller::drawBoard(SDL_Renderer* renderer)
{

}

void Controller::drawMino(SDL_Renderer* renderer, int mino, int rotation, int x, int y)
{
	/*char pixel;
	for (int i = 0; i < MINO_DIM; i++) {
		for (int j = 0; j < MINO_DIM; j++) {
			pixel = minoes->getMino(mino, rotation, i, j);
			//boxColor(surface, -, -, -, -, RED); still need to calculate
		}
	}*/
}