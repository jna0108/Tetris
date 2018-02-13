#pragma once

// #ifndef TETROMINO_H #define TETROMINO_H #endif ???
class Tetromino
{
public:
	// Returns character at specified mino coordinates
	// (Return pointer to array or bmp and index at once instead of multiple function calls?)
	char getMino(int mino, int rotation, int row, int col);
};

