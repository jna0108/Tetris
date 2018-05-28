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
	int cMino, cRot;
	float cX, cY;				// current piece

	// Tile textures, but library won't link properly
	// void setTextures(SDL_Texture* I_texture, SDL_Texture* J_texture, SDL_Texture* L_texture, SDL_Texture* O_texture, SDL_Texture* S_texture, SDL_Texture* T_texture, SDL_Texture* Z_texture);
private:
	Board *board;
	Tetromino *minoes;
	int nMino;								// next piece
	const int nRot = 0, nX = 12, nY = 2;	// next piece's fields are always the same
	
	//SDL_Texture *I, *J, *L, *O, *S, *T, *Z;

	void initGame();
	void drawBoard(SDL_Renderer* renderer);
	void drawMino(SDL_Renderer* renderer, int mino, int rotation, float x, float y);
};