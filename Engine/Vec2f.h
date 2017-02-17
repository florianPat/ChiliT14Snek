#pragma once
struct Vec2
{
	Vec2(int x, int y) : x(x), y(y) {};
	Vec2 operator+=(const Vec2& input)
	{
		x += input.x;
		y += input.y;
		return *this;
	}
	bool operator==(const Vec2& input)
	{
		return( (x == input.x) && (y == input.y) );
	}
	int x, y;
};