#pragma once

#include "Graphics.h"
#include "Vec2f.h"

class Board
{
	int numberOfCells;
	int sizeofCells;
	Graphics& gfx;
public:
	Board(Graphics& gfx, int numberOfCells = 40, int sizeofCells = 10);
	void drawCell(const Vec2 & vec2, Color c);
};