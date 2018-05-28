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
	if (nMino == 1) {
		drawMino(renderer, nMino, nRot, nX - 0.5, nY - 0.5);
	} else if (nMino == 2) {
		drawMino(renderer, nMino, nRot, nX - 0.5, nY);
	} else {
		drawMino(renderer, nMino, nRot, nX, nY);
	}
	
}

void Controller::generatePiece()
{
	// Make next piece the current piece
	cMino = nMino;
	cRot = nRot;
	cX = 2;
	cY = -1;

	// Spawn next piece
	nMino = rand() % 7;
}

/*void Controller::setTextures(SDL_Texture * I_texture, SDL_Texture * J_texture, SDL_Texture * L_texture, SDL_Texture * O_texture, SDL_Texture * S_texture, SDL_Texture * T_texture, SDL_Texture * Z_texture)
{
	I = I_texture;
	J = J_texture;
	L = L_texture;
	O = O_texture;
	S = S_texture;
	T = T_texture;
	Z = Z_texture;
}*/

void Controller::initGame()
{
	// Spawn initial piece
	cMino = rand() % 7; // 0 to 6
	cRot = 0, cX = 2, cY = -1; // initial rotation and spawn location

	// Spawn initial next piece
	nMino = rand() % 7;
}

void Controller::drawBoard(SDL_Renderer* renderer)
{
	for (int i = 0; i < board->height; i++) {
		for (int j = 0; j < board->width; j++) {
			if (!board->isFreeSpace(i, j)) {
				SDL_Rect block = { board->origX + j * board->block_dim + 1, board->origY + i * board->block_dim + 1, board->block_dim - 2, board->block_dim - 2 };
				
				/* 
				switch (board->getBlock(i, j)) {
				case 1:
					SDL_RenderCopy(renderer, T, NULL, &block);
					break;
				case 2:
					SDL_RenderCopy(renderer, I, NULL, &block);
					break;
				case 3:
					SDL_RenderCopy(renderer, O, NULL, &block);
					break;
				case 4:
					SDL_RenderCopy(renderer, J, NULL, &block);
					break;
				case 5:
					SDL_RenderCopy(renderer, L, NULL, &block);
					break;
				case 6:
					SDL_RenderCopy(renderer, S, NULL, &block);
					break;
				case 7:
					SDL_RenderCopy(renderer, Z, NULL, &block);
					break;
				}
				*/

				switch (board->getBlock(i, j)) {
					case 1:
						SDL_SetRenderDrawColor(renderer, 226, 66, 244, 0xFF);
						break;
					case 2:
						SDL_SetRenderDrawColor(renderer, 78, 226, 252, 0xFF);
						break;
					case 3:
						SDL_SetRenderDrawColor(renderer, 244, 247, 79, 0xFF);
						break;
					case 4:
						SDL_SetRenderDrawColor(renderer, 19, 43, 219, 0xFF);
						break;
					case 5:
						SDL_SetRenderDrawColor(renderer, 232, 127, 16, 0xFF);
						break;
					case 6:
						SDL_SetRenderDrawColor(renderer, 19, 239, 52, 0xFF);
						break;
					case 7:
						SDL_SetRenderDrawColor(renderer, 226, 27, 27, 0xFF);
						break;
				}
				SDL_RenderFillRect(renderer, &block);
			}
		}
	}
}

void Controller::drawMino(SDL_Renderer* renderer, int mino, int rotation, float x, float y)
{
	int pX = board->origX + x * board->block_dim;
	int pY = board->origY + y * board->block_dim;
	for (int j = 0; j < MINO_DIM; j++) {
		for (int i = 0; i < MINO_DIM; i++) {
			uint8_t pixel = minoes->getMino(mino, rotation, j, i);
			if (pixel > 0) {
				SDL_Rect border = { pX + i * board->block_dim - 1, pY + j * board->block_dim - 1, board->block_dim + 2, board->block_dim + 2 };
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderDrawRect(renderer, &border);

				SDL_Rect block = { pX + i * board->block_dim, pY + j * board->block_dim, board->block_dim, board->block_dim};
				switch (pixel) {
					case 1:
						SDL_SetRenderDrawColor(renderer, 226, 66, 244, 0xFF);
						break;
					case 2:
						SDL_SetRenderDrawColor(renderer, 78, 226, 252, 0xFF);
						break;
					case 3:
						SDL_SetRenderDrawColor(renderer, 244, 247, 79, 0xFF);
						break;
					case 4:
						SDL_SetRenderDrawColor(renderer, 19, 43, 219, 0xFF);
						break;
					case 5:
						SDL_SetRenderDrawColor(renderer, 232, 127, 16, 0xFF);
						break;
					case 6:
						SDL_SetRenderDrawColor(renderer, 19, 239, 52, 0xFF);
						break;
					case 7:
						SDL_SetRenderDrawColor(renderer, 226, 27, 27, 0xFF);
						break;
				}

				SDL_RenderFillRect(renderer, &block);
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderDrawRect(renderer, &block);
			}
		}
	}
}