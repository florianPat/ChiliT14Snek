#include "Snake.h"

Snake::Snake(const Vec2& loc, int nStartingBodyTiles, Board& board) : board(board)
{
	segments[0].InitHead(loc);
	for (int i = 0; i < nStartingBodyTiles; i++)
	{
		Grow();
		MoveBy(right);
	}
}

void Snake::MoveBy(MoveLocation newLoc)
{
	for (int i = nUsedSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(newLoc);
	for (int i = 0; i < nUsedSegments - 1; i++)
	{
		board.SetTileTypeAtPos(segments[i].GetPosition(), Board::TileType::Snake);
	}
}

void Snake::Grow()
{
	if (nUsedSegments < nMaxSegments)
	{
		segments[nUsedSegments].InitBody(segments[nUsedSegments - 1].GetIndex());
		nUsedSegments++;
	}
}

void Snake::Draw()
{
	for (int i = 0; i < nUsedSegments; i++)
	{
		segments[i].Draw(board);
	}
}

bool Snake::hitItselfAfterDeltaPos(MoveLocation deltaPos)
{
	for (int i = 0; i < nUsedSegments - 1; i++)
	{
		if (GetHeadPosAfterDeltaMove(deltaPos) == segments[i].GetPosition())
		{
			return true;
		}
	}
	return false;
}

bool Snake::posIsInsideHead(const Vec2 & loc, MoveLocation deltaPos)
{
	Segment head = segments[0];
	head.MoveBy(deltaPos);
	if (head.GetPosition() == loc)
		return true;
	else
		return false;
}

Vec2 Snake::GetHeadPos() const
{
	return segments[0].GetPosition();
}

Vec2 Snake::GetHeadPosAfterDeltaMove(MoveLocation moveLoc)
{
	Segment head = segments[0];
	head.MoveBy(moveLoc);
	return head.GetPosition();
}

Snake::Segment::Segment() : position(0, 0), color(Snake::headColor), index(0)
{
}

void Snake::Segment::InitHead(const Vec2& pos)
{
	position = pos;
	color = Snake::headColor;
}

void Snake::Segment::Draw(Board & board)
{
	board.drawCell(position, color);
}

void Snake::Segment::Follow(const Segment & segment)
{
	position = segment.position;
}

void Snake::Segment::MoveBy(MoveLocation newLoc)
{
	Vec2 newPos(0,0);

	switch (newLoc)
	{
		case right:
		{
			newPos.x = 1;
			newPos.y = 0;
		}	break;
		case left:
		{
			newPos.x = -1;
			newPos.y = 0;
		}	break;
		case top:
		{
			newPos.x = 0;
			newPos.y = -1;
		}	break;
		case bottom:
		{
			newPos.x = 0;
			newPos.y = 1;
		}	break;
	}

	position += newPos;
}

Vec2 Snake::Segment::GetPosition() const
{
	return position;
}

int Snake::Segment::GetIndex() const
{
	return index;
}

void Snake::Segment::InitBody(const int lastIndex)
{
	if (lastIndex < 2)
	{
		int newLastIndex = lastIndex;
		index = ++newLastIndex;
	}
	else
		index = 0;

	color = bodyColor[index];
}
