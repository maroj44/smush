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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
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
	detectInput();
	updatePos();
	checkBounds();
	checkStage();
	//changeColor();
	
}

void Game::createBox(int x, int y)
{
	gfx.PutPixel(x + boxSize, y + boxSize, 0, 255, 0);
	gfx.PutPixel(x - boxSize, y + boxSize, 0, 255, 0);
	gfx.PutPixel(x + boxSize, y - boxSize, 0, 255, 0);
	gfx.PutPixel(x - boxSize, y - boxSize, 0, 255, 0);
}

void Game::createStage(int length, int height)
{
	//centering
	int x, y;
	x = (gfx.ScreenWidth - length) / 2;
	y = (gfx.ScreenHeight - height) / 2;
	for (int i = 0; i < length; i++)
	{
		gfx.PutPixel(x + i, y, 255, 255, 255);
		gfx.PutPixel(x + i, y + height - 1, 255, 255, 255);
	}
	for (int j = 0; j < height; j++)
	{
		gfx.PutPixel(x, y + j, 255, 255, 255);
		gfx.PutPixel(x + length, y + j, 255, 255, 255);
	}
}

/*
bool Game::checkCollision(int x, int y, int fX, int fY)
{
	const int top = y - boxSize;
	const int bottom = y + boxSize;
	const int left = x - boxSize;
	const int right = x + boxSize;

	const int fTop = fY - boxSize;
	const int fBottom = fY + boxSize;
	const int fLeft = fX - boxSize;
	const int fRight = fX + boxSize;

	return (left < fRight && right > fLeft && top < fBottom && bottom > fTop);
	
}
*/

void Game::checkBounds()
{
	if (x + boxSize >= gfx.ScreenWidth) {
		x = gfx.ScreenWidth - boxSize - 1;
		vx = 0;
	}
	if (x - boxSize < 0) {
		x = boxSize;
		vx = 0;
	}
	if (y + boxSize >= gfx.ScreenHeight) {
		y = gfx.ScreenHeight - boxSize - 1;
		vy = 0;
	}
	if (y - boxSize < 0) {
		y = boxSize;
		vy = 0;
	}
}

void Game::checkStage() //fix other sides
{
	if (y >= (gfx.ScreenHeight - stageHeight) / 2 - boxSize - 1 && y <= (gfx.ScreenHeight - stageHeight) / 2 - boxSize + stageHeight - 1 
		&& x >= (gfx.ScreenWidth - stageLength) / 2 && x <= (gfx.ScreenWidth - stageLength) / 2 + stageLength)
	{
		if(vy > 0)
		{
		y = (gfx.ScreenHeight - stageHeight) / 2 - boxSize - 1;
		vy = 0;
		}
	}
}



void Game::detectInput()
{
	if (wnd.kbd.KeyIsPressed(0x57) || wnd.kbd.KeyIsPressed(VK_UP)) { //w or up
		if (!inhibitUp) {
			vy = vy - 1;
			inhibitUp = true;
		}
	}
	else {
		inhibitUp = false;
	}

	if (wnd.kbd.KeyIsPressed(0x41) || wnd.kbd.KeyIsPressed(VK_LEFT)) { //a or left
		if (!inhibitLeft) {
			vx = vx - 1;
			inhibitLeft = true;
		}

	}
	else {
		inhibitLeft = false;
	}

	if (wnd.kbd.KeyIsPressed(0x53) || wnd.kbd.KeyIsPressed(VK_DOWN)) { //s or down
		if (!inhibitDown) {
			vy = vy + 1;
			inhibitDown = true;
		}
	}
	else {
		inhibitDown = false;
	}

	if (wnd.kbd.KeyIsPressed(0x44) || wnd.kbd.KeyIsPressed(VK_RIGHT)) { //d or right
		if (!inhibitRight) {
			vx = vx + 1;
			inhibitRight = true;
		}
	}
	else {
		inhibitRight = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		vx = 0;
		vy = 0;
	}

	shapeIsChanged = wnd.kbd.KeyIsPressed(VK_SHIFT);
}

void Game::updatePos()
{
	x = x + vx;
	y = y + vy;
}

/*void Game::changeColor()
{
	colliding = checkCollision(x, y, fixedCenterX, fixedCenterY) || checkCollision(x, y, b2X, b2Y);

	if (wnd.kbd.KeyIsPressed(VK_CONTROL) || (x > valleyLeft && x < valleyRight) || colliding) {
		gb = 0;
	}
	else {
		gb = 255;
	}
}
*/

void Game::ComposeFrame()
{
	for (int i = 0; i <= 5 && !shapeIsChanged; i++) {
		gfx.PutPixel(x + i, y, 255, gb, gb);
		gfx.PutPixel(x - i, y, 255, gb, gb);
		gfx.PutPixel(x, y + i, 255, gb, gb);
		gfx.PutPixel(x, y - i, 255, gb, gb);
	}

	if (shapeIsChanged) {
		gfx.PutPixel(x + 5, y + 5, 255, gb, gb);
		gfx.PutPixel(x - 5, y + 5, 255, gb, gb);
		gfx.PutPixel(x + 5, y - 5, 255, gb, gb);
		gfx.PutPixel(x - 5, y - 5, 255, gb, gb);
	}

	//createBox(fixedCenterX, fixedCenterY);

	//createBox(b2X, b2Y);

	createStage(stageLength, stageHeight);
	
}
