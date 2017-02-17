#pragma once

#include "Vec2f.h"
#include "Board.h"
#include "Colors.h"
#include <random>

class Goal
{
public:
	Goal(Board& brd);
	void Respawn(const Vec2& snakeLoc);
	void Draw();
	Vec2 getPosition() const;

private:
	Board& brd;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist, yDist;
	Vec2 position;
	const Color color = Colors::Yellow;
};

