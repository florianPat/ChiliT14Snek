#pragma once

#include "Vec2f.h"
#include "Board.h"
#include "Colors.h"

class Snake
{
public:

	enum moveLocation
	{
		right, left, top, bottom
	};

	Snake(const Vec2& loc);

	void MoveBy(moveLocation newLoc);
	void Grow();
	void Draw(Board& board);
private:
	class Segment
	{
		Vec2 position;
		Color color;

	public:
		Segment();
		void InitHead(const Vec2& pos);
		void InitBody();
		void Draw(Board& board);
		void Follow(const Segment& segment);
		void MoveBy(moveLocation newLoc);
	};

	static constexpr Color headColor = Colors::Red;
	static constexpr Color bodyColor = Colors::Green;

	static constexpr int nMaxSegments = 100;
	int nUsedSegments = 1;
	Segment segments[nMaxSegments];
};