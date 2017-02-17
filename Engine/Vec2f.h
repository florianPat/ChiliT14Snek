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
	int x, y;
};