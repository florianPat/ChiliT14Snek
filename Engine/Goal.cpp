#include "Goal.h"
#include "Snake.h"

Goal::Goal(Board& brd, const Snake& snake) : brd(brd), snake(snake), rd(), rng(rd()), 
	xDist(0, brd.GetWidth()), yDist(0, brd.GetHeight()), position(xDist(rng), yDist(rng))
{
	Respawn();
}

void Goal::Respawn()
{
	do
	{
		position.x = xDist(rng);
		position.y = yDist(rng);
	} while (position == snake.GetHeadPos() && brd.GetTileTypeAtPos(position) != Board::TileType::Empty);
	brd.SetTileTypeAtPos(position, Board::TileType::Food);
}

void Goal::Draw()
{
	brd.drawCell(position, color);
}