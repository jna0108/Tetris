// Tetris.cpp : Defines the entry point for the console application.

/*
	General Tetris Game Loop:
		while(game is running)
			check for user input
			move blocks
				resolve collisions
			check for line clears
			draw graphics
			play sounds
		end while

	Game (ha) plan:
		1. Different classes
			Game window (covered by SDL)
			Tetronimos (Arrays?)
			Game board (boundaries, collisions)
		2. Display the board and tetronimos
			Clear the board when game is "over" (exit or loss)
		3. Have the tetronimos move down over time 
		4. Detect collision with ground and each other
			Maybe have tetronimos become part of the ground
			after touching base?
		5. Ability to move tetronimo with user input
		6. Ability to rotate tetronimo
		7. Line detection and clearing
		8. Tracking scores
		9. Next upcoming piece
*/

#include "stdafx.h" // Ask Carey about this -- is it necessary?
#include <SDL.h>
#include <stdio.h>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Note to self, SDL requires these args
int main(int argc, char* args[])
{
	// Game window
	SDL_Window* window = NULL;

	// Surface inside of window
	SDL_Surface* surface = NULL;

	//Initialize SDL Video Subsytem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Unable to create window: %s\n", SDL_GetError());
		}
		else
		{
			// Set surface
			surface = SDL_GetWindowSurface(window);

			// Make it white
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

			// Update it
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}