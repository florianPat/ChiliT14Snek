#include "Goal.h"

Goal::Goal(Board& brd) : brd(brd), rd(), rng(rd()), xDist(0, brd.GetDimension()), yDist(0, brd.GetDimension()), 
						 position(xDist(rng), yDist(rng))
{
}

void Goal::Respawn(const Vec2& snakeLoc)
{
	do
	{
		position.x = xDist(rng);
		position.y = yDist(rng);
	} while (position == snakeLoc);
}

void Goal::Draw()
{
	brd.drawCell(position, color);
}

Vec2 Goal::getPosition() const
{
	return position;
}
