#include "stdafx.h"
#include "Tetromino.h"

// 7 Mino Types, 4 Rotations per type
char Tetrominoes[1 /*will eventually be 7*/][4][5][5] = {
	// T Tetromino
	{
		// Top orientation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
			// potential future optimization(?): represent as bmp
			// definitely a better way to represent this
		},
		// Right orientation
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		// Bottom orientation
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		// Left orientation
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
	}
};

char Tetromino::getMino(int num, int rotation, int row, int col)
{
	return Tetrominoes[num][rotation][row][col];
}