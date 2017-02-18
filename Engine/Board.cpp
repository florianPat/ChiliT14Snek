#include "Board.h"

Board::Board(Graphics& gfx, int sizeofCells) : sizeofCells(sizeofCells), gfx(gfx), rd(), rng(rd()),
	xDist(0, GetWidth()), yDist(0, GetHeight())
{
}

void Board::drawCell(const Vec2 & vec2, Color c)
{
	gfx.DrawRect(Vec2(vec2.x * sizeofCells, vec2.y * sizeofCells), sizeofCells, sizeofCells, c);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
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

void Board::DrawObstacles()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (GetTileTypeAtPos(x, y) == TileType::Obstacle)
				drawCell(Vec2(x ,y), obstacleColor);
		}
	}
}
