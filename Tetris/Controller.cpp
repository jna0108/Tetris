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
	drawMino(renderer, nMino, nRot, nX, nY);
}

void Controller::generatePiece()
{
	// Make next piece the current piece
	cMino = nMino;
	cRot = nRot;
	cX = 2;
	cY = -1;

	// Spawn next piece
	//nMino = rand() % 7;
}

void Controller::initGame()
{
	// Spawn initial piece
	//cMino = rand() % 7; // 0 to 6
	cMino = 0;
	cRot = 3, cX = 2, cY = -1; // initial rotation and spawn location

	// Spawn initial next piece
	//nMino = rand() % 7;
	nMino = 0;
}

void Controller::drawBoard(SDL_Renderer* renderer)
{
	for (int i = 0; i < board->height; i++) {
		for (int j = 0; j < board->width; j++) {
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
	int pX = board->origX + x * board->block_dim;
	int pY = board->origY + y * board->block_dim;
	for (int i = 0; i < MINO_DIM; i++) {
		for (int j = 0; j < MINO_DIM; j++) {
			char pixel = minoes->getMino(mino, rotation, i, j);
			if (pixel) {
				SDL_Rect border = { pX + i * board->block_dim - 1, pY + j * board->block_dim - 1, board->block_dim + 2, board->block_dim + 2 };
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderDrawRect(renderer, &border);

				SDL_Rect block = { pX + i * board->block_dim, pY + j * board->block_dim, board->block_dim, board->block_dim};
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(renderer, &block);
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderDrawRect(renderer, &block);
			}
		}
	}
}