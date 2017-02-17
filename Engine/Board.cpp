#include "Board.h"

Board::Board(Graphics& gfx, int numberOfCells, int sizeofCells) : numberOfCells(numberOfCells), sizeofCells(sizeofCells), gfx(gfx)
{
}

void Board::drawCell(const Vec2 & vec2, Color c)
{
	gfx.DrawRect(Vec2(vec2.x * sizeofCells, vec2.y * sizeofCells), sizeofCells, sizeofCells, c);
}
