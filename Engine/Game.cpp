/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	snake({ 2, 2 }, 3, board),
	goal(board, snake)
{
	board.SpawnPoison(275);
	board.SpawnObstacle(90);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (title)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			title = false;
	}
	else
	{
		if (!gameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				newLoc = snake.top;
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				newLoc = snake.bottom;
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				newLoc = snake.left;
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				newLoc = snake.right;
			}

			if (needUpdate <= 0)
			{
				Vec2 snakeNextHeadLoc = snake.GetHeadPosAfterDeltaMove(newLoc);

				switch(board.GetTileTypeAtPos(snakeNextHeadLoc))
				{
					case Board::TileType::Food:
					{
						snake.Grow();
						goal.Respawn();
					}	break;
					case Board::TileType::Obstacle:
					{
						gameOver = true;
					}	break;
					case Board::TileType::Poisons:
					{
						if (needUpdatePeriod > 1)
							needUpdatePeriod -= 2;
						board.SetTileTypeAtPos(snakeNextHeadLoc, Board::TileType::Empty);
					}	break;
				}

				if (snake.hitItselfAfterDeltaPos(newLoc))
				{
					gameOver = true;
				}
				
				if (snakeNextHeadLoc.x < 0 || snakeNextHeadLoc.x > board.GetWidth() - 1 || snakeNextHeadLoc.y < 0 ||
					snakeNextHeadLoc.y > board.GetHeight() - 1)
					gameOver = true;

				if(!gameOver)
					snake.MoveBy(newLoc);

				needUpdate = needUpdatePeriod;
			}
			--needUpdate;
		}
	}
}

void Game::ComposeFrame()
{
	if (gameOver)
		SpriteCodex::DrawGameOver(300, 200, gfx);
	else if (title)
		SpriteCodex::DrawTitle(300, 200, gfx);
	else
	{
		snake.Draw();
		goal.Draw();
		board.DrawObstaclesAndPoison();
		board.drawBorder(Colors::Blue);
	}
}
