#pragma once

class Tetromino
{
public:
	// Returns character at specified mino coordinates
	// (Return pointer to array or bmp and index at once instead of multiple function calls?)
	uint8_t getMino(int mino, int rotation, int row, int col);
};