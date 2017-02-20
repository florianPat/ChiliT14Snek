#include "Board.h"

Board::Board(Graphics& gfx, int sizeofCells, int startBoardPos, int padding) : sizeofCells(sizeofCells), startBoardPos(startBoardPos), padding(padding), gfx(gfx), rd(), rng(rd()),
	xDist(0, GetWidth()), yDist(0, GetHeight())
{
}

void Board::drawCell(const Vec2 & vec2, Color c)
{
	gfx.DrawRect(Vec2(vec2.x * sizeofCells + startBoardPos * sizeofCells + padding, vec2.y * sizeofCells + startBoardPos * sizeofCells + padding), sizeofCells - padding, sizeofCells - padding, c);
}

void Board::drawBorder(Color c)
{
	for (int i = -1; i < width; i++)
	{
		drawCell({ i, -1 }, c);
		drawCell({ i, -1 + height}, c);
	}
	for (int i = -1; i < height; i++)
	{
		drawCell({ -1, i }, c);
		drawCell({ -1 + width, i }, c);
	}
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

int Board::GetStartBoardPos() const
{
	return startBoardPos;
}

Board::TileType Board::GetTileTypeAtPos(int x, int y) const
{
	return tileType[y * width + x];
}

Board::TileType Board::GetTileTypeAtPos(Vec2 pos) const
{
	return GetTileTypeAtPos(pos.x, pos.y);
}

void Board::SetTileTypeAtPos(int x, int y, TileType in_tileType)
{
	tileType[y * width + x] = in_tileType;
}

void Board::SetTileTypeAtPos(Vec2 pos, TileType tileType)
{
	SetTileTypeAtPos(pos.x, pos.y, tileType);
}

void Board::SpawnObstacle(int numberOfObstacles)
{
	for (int i = 0; i < numberOfObstacles; i++)
	{
		Vec2 position = { 0,0 };
		do
		{
			position.x = xDist(rng);
			position.y = yDist(rng);
		} while (GetTileTypeAtPos(position) != Board::TileType::Empty);
		SetTileTypeAtPos(position, Board::TileType::Obstacle);
	}
}

void Board::DrawObstaclesAndPoison()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (GetTileTypeAtPos(x, y) == TileType::Obstacle)
				drawCell(Vec2(x, y), obstacleColor);
			else if (GetTileTypeAtPos(x, y) == TileType::Poisons)
				drawCell(Vec2(x, y), poisonColor);
		}
	}
}

void Board::SpawnPoison(int numberOfPoisons)
{
	for (int i = 0; i < numberOfPoisons; i++)
	{
		Vec2 position = { 0,0 };
		do
		{
			position.x = xDist(rng);
			position.y = yDist(rng);
		} while (GetTileTypeAtPos(position) != Board::TileType::Empty);
		SetTileTypeAtPos(position, Board::TileType::Poisons);
	}
}
