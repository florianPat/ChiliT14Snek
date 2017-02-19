#pragma once

#include "Vec2f.h"
#include "Board.h"
#include "Colors.h"

class Snake
{
public:

	enum MoveLocation
	{
		right, left, top, bottom
	};

	Snake(const Vec2& loc, int nStartingBodyTiles, Board& board);

	void MoveBy(MoveLocation newLoc);
	void Grow();
	void Draw();
	bool hitItselfAfterDeltaPos(MoveLocation deltaPos);
	bool posIsInsideHead(const Vec2& loc, MoveLocation deltaPos);
	Vec2 GetHeadPos() const;
	Vec2 GetHeadPosAfterDeltaMove(MoveLocation moveLoc);
private:
	class Segment
	{
		Vec2 position;
		Color bodyColor[3] = { Colors::MakeRGB(0u, 90u, 0u), Colors::MakeRGB(0u, 180u, 0u), Colors::MakeRGB(0u, 255u, 0u) };
		Color color;
		int index;

	public:
		Segment();
		void InitHead(const Vec2& pos);
		void InitBody(const int lastIndex);
		void Draw(Board& board);
		void Follow(const Segment& segment);
		void MoveBy(MoveLocation newLoc);
		Vec2 GetPosition() const;
		int GetIndex() const;
	};

private:
	static constexpr Color headColor = Colors::Red;
	static constexpr int nMaxSegments = 100;
	int nUsedSegments = 1;
	Segment segments[nMaxSegments];

	Board& board;
};