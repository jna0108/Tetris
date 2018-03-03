// Tetris.cpp : Defines the entry point for the console application.

/*
	General Tetris Game Loop:
		while(game is running)
			check for user input
			move blocks
				resolve collisions
			check for line clears
			draw graphics
				clear screen
				controller.draw
			play sounds
		end while

	Game (ha) plan:
		1. Different classes (DONE)
			Game logic (covered by SDL)
			Tetronimos (Arrays?)
			Game board (boundaries, collisions)
		2. Display the board and tetronimos
			Clear the board when game is "over" (exit or loss)
		3. Have the tetronimos move down over time 
		4. Detect collision with ground and each other (DONE)
			Maybe have tetronimos become part of the ground
			after touching base? (DONE)
		5. Ability to move tetronimo with user input
		6. Ability to rotate tetronimo
		7. Line detection and clearing (DONE)
		8. Tracking scores
		9. Next upcoming piece

	Current To-Do List:
		Finish controller (drawing, starting the game)
		Game logic in main (Tetris.cpp)
			init the game
			check for user input
			move tetromino
			spawn new piece if necessary
			controller.draw()
*/

#include "stdafx.h"
#include "Board.h"
#include "Tetromino.h"
#include "Controller.h"

// Screen dimensions
const int SCREEN_WIDTH = 560;
const int SCREEN_HEIGHT = 700;

// Initialize SDL
bool init();

// Close SDL
void close();

// Game window
SDL_Window* window = NULL;

// Surface inside window--don't think I need this or texture
//SDL_Surface* surface = NULL;
//L_Texture* texture;

// Game renderer
SDL_Renderer* renderer = NULL;

/****************************************************/
bool init() {
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
				//Initialize renderer color to white
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return true;
}

void close() {
	// Clean up everything
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	SDL_Quit();
}

// Note to self, SDL requires these args
int main(int argc, char* args[]) {
	if (!init()) {
		printf("Initialization Error\n");
	} else {
		bool quit = false;
		SDL_Event e;	
		Tetromino minoes;
		Board board(&minoes, SCREEN_WIDTH / 7, 110, 24);
		Controller game(&board, &minoes);

		// Main game loop
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				// User closes window.
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
			
			// Move the pieces
			

			// Clear screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			// Draw board outline (1 pixel outside)
			SDL_Rect border = { SCREEN_WIDTH / 7 - 1, 109, 242, 482 };
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			for (int i = 0; i < board.height; i++) {
				for (int j = 0; j < board.width; j++) {
					SDL_Rect grid = { board.origX + j * board.block_dim, board.origY + i * board.block_dim, board.block_dim, board.block_dim };
					SDL_RenderDrawRect(renderer, &grid);
				}
			}
			SDL_RenderDrawRect(renderer, &border);

			game.draw(renderer);

			board.detectLines();

			// Draw everything
			SDL_RenderPresent(renderer);
			SDL_Delay(700);
			/***************************EXAMPLE CODE********************************

			//Render red filled quad
			SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &fillRect);

			//Render green outlined quad
			SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(renderer, &outlineRect);

			//Draw blue horizontal line
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

			//Draw vertical line of yellow dots
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
			for (int i = 0; i < SCREEN_HEIGHT; i += 4)
			{
				SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
			}

			//Update screen
			SDL_RenderPresent(renderer);
			SDL_Delay(700);

			/***********************************************************************/
			// Update surface (OUTDATED)
			//SDL_UpdateWindowSurface(window);
		}
	}

	close();
	return 0;
}