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
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (!board->isFreeSpace(i, j)) {
				SDL_Rect block = { board->origX + j * board->block_dim + 1, board->origY + i * board->block_dim + 1, board->block_dim - 2, board->block_dim - 2 };
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(renderer, &block);
			}
		}
	}
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