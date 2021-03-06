// Tetris.cpp : Defines the entry point for the console application.

/*
	To-Do List for the Future:
		Redo project with proper libraries for textures
		Hold Piece
		Rotate a piece near the sides
		Score
		Game speeds up as time goes on
		Fix sloppy data conversions
*/

#include "stdafx.h"
#include "Board.h"
#include "Tetromino.h"
#include "Controller.h"

// Screen dimensions
const int SCREEN_WIDTH = 560;
const int SCREEN_HEIGHT = 700;
const int TIME = 700;

// Initialize SDL
bool init();

// Close SDL
void close();

// Game window
SDL_Window* window = NULL;

// Game renderer
SDL_Renderer* renderer = NULL;

// Tile Textures
// SDL_Texture *I, *J, *L, *O, *S, *T, *Z;

/****************************************************/
bool init() {
	// Seed random number
	srand(time(NULL));

	//Initialize SDL Video Subsytem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	} else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Linear texture filtering disabled");
		}

		//Create window
		window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Unable to create window: %s\n", SDL_GetError());
			return false;
		} else {
			// Set surface and make it white
			//surface = SDL_GetWindowSurface(window);
			//SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
		
			// Set renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Unable to set renderer: %s\n", SDL_GetError());
				return false;
			} else {
				//Initialize renderer color to gray
				SDL_SetRenderDrawColor(renderer, 0xAE, 0xAE, 0xAE, 0xFF);
			}
		}
	}

	/*
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	
	// Load textures
	SDL_Surface* loadedSurface = IMG_Load("assets/I.png");
	I = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load("assets/J.png");
	J = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load("assets/L.png");
	L = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load("assets/O.png");
	O = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load("assets/S.png");
	S = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load("assets/T.png");
	T = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load("assets/Z.png");
	Z = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	SDL_FreeSurface(loadedSurface);*/
	
	return true;
}

void close() {
	// Clean up everything

	/*SDL_DestroyTexture(I);
	SDL_DestroyTexture(J);
	SDL_DestroyTexture(L);
	SDL_DestroyTexture(O);
	SDL_DestroyTexture(S);
	SDL_DestroyTexture(T);
	SDL_DestroyTexture(Z);
	I = J = L = O = S = T = Z = NULL;*/

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	//IMG_Quit();
	SDL_Quit();
}

// Note to self, SDL requires these args
int main(int argc, char* args[]) {
	if (!init()) {
		printf("Initialization Error\n");
	} else {
		bool quit = false;
		uint32_t startTime = SDL_GetTicks();
		SDL_Event e;	
		Tetromino minoes;
		Board board(&minoes, SCREEN_WIDTH / 7, 110, 24);
		Controller game(&board, &minoes);

		//game.setTextures(I, J, L, O, S, T, Z);

		// Main game loop
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				// User closes window
				if (e.type == SDL_QUIT) {
					quit = true;
				}

				// User presses a key
				else if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
						case SDLK_RIGHT:
							if (board.isValidMove(game.cX + 1, game.cY, game.cMino, game.cRot)) {
								game.cX++;
							}
							break;
						case SDLK_LEFT:
							if (board.isValidMove(game.cX - 1, game.cY, game.cMino, game.cRot)) {
								game.cX--;
							}
							break;
						case SDLK_DOWN:
							if (board.isValidMove(game.cX, game.cY + 1, game.cMino, game.cRot)) {
								game.cY++;
							}
							break;
						case SDLK_a:
							if (board.isValidMove(game.cX, game.cY, game.cMino, (game.cRot + 3) % 4)) {
								game.cRot = (game.cRot + 3) % 4;
							}
							break;
						case SDLK_d:
							if (board.isValidMove(game.cX, game.cY, game.cMino, (game.cRot + 1) % 4)) {
								game.cRot = (game.cRot + 1) % 4;
							}
							break;
						case SDLK_SPACE:
							while (board.isValidMove(game.cX, game.cY + 1, game.cMino, game.cRot)) {
								game.cY++;
							}
							
							// Add piece to board
							board.addToBoard(game.cX, game.cY, game.cMino, game.cRot);
							
							// Clear full lines
							board.detectLines();

							// Detect game over
							if (board.isGameOver()) {
								quit = true;
							}

							// Get new piece
							game.generatePiece();
							break;
					}
				}
			}
		
			// Clear screen
			SDL_SetRenderDrawColor(renderer, 0xAE, 0xAE, 0xAE, 0xFF);
			SDL_RenderClear(renderer);

			// Draw board outline (1 pixel outside)
			SDL_Rect border = { SCREEN_WIDTH / 7 - 1, 109, 242, 482 };
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			for (int i = 0; i < board.height; i++) {
				for (int j = 0; j < board.width; j++) {
					SDL_Rect grid = { board.origX + j * board.block_dim, board.origY + i * board.block_dim, board.block_dim, board.block_dim };
					SDL_RenderDrawRect(renderer, &grid);
				}
			}
			SDL_RenderDrawRect(renderer, &border);

			// Draw HOLD and NEXT boxes
			//SDL_Rect hold = {};
			SDL_Rect next = { SCREEN_WIDTH / 7 + 12 * 24, 110 + 2 * 24, 120, 96 };
			SDL_Rect next_border = { SCREEN_WIDTH / 7 + 12 * 24 - 1, 110 + 2 * 24 - 1, 122, 98 };
			//SDL_RenderDrawRect(renderer, &hold);
			SDL_RenderDrawRect(renderer, &next);
			SDL_RenderDrawRect(renderer, &next_border);


			// Draw board and pieces
			game.draw(renderer);

			// Present everything to renderer
			SDL_RenderPresent(renderer);
			
			// Move piece down
			if (SDL_GetTicks() - startTime > 700) {
				// Check if piece can get moved
				if (board.isValidMove(game.cX, game.cY + 1, game.cMino, game.cRot)) {
					game.cY++;
				} else {
					// Add piece to board
					board.addToBoard(game.cX, game.cY, game.cMino, game.cRot);
					
					// Clear full lines
					board.detectLines();

					// Detect game over
					if (board.isGameOver()) {
						quit = true;
					}

					// Get new piece
					game.generatePiece();					
				}
				startTime = SDL_GetTicks();
			}
		}
	}

	close();
	return 0;
}