#pragma once

#include "Graphics.h"
#include "Vec2f.h"
#include <random>

class Board
{
public:
	enum class TileType
	{
		Empty, SnakeHead, Obstacle, Food
	};
private:
	static constexpr int width = 40, height = 40;
	TileType tileType[width * height] = { TileType::Empty };
	const int sizeofCells;
	Graphics& gfx;

	Color obstacleColor = Colors::Gray;

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist, yDist;
public:
	Board(Graphics& gfx, int sizeofCells = 10);
	void drawCell(const Vec2 & vec2, Color c);
	int GetWidth() const;
	int GetHeight() const;
	TileType GetTileTypeAtPos(int x, int y) const;
	TileType GetTileTypeAtPos(Vec2 pos) const;
	void SetTileTypeAtPos(int x, int y, TileType tileType);
	void SetTileTypeAtPos(Vec2 pos, TileType tileType);

	void SpawnObstacle(int numberOfObstacles);
	void DrawObstacles();
};