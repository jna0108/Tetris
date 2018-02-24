#include "stdafx.h"
#include "Controller.h"

Controller::Controller(Board * board, Tetromino * minoes)
{
	this->board = board;
	this->minoes = minoes;
}

void Controller::draw()
{
	drawBoard();
	drawMino();
}

void Controller::generatePiece()
{

}

void Controller::initGame()
{
}

void Controller::drawBoard()
{

}

void Controller::drawMino()
{
}
