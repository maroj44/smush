/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void createBox(int x, int y);
	void createStage(int length, int height);
	//bool checkCollision(int x, int y, int fX, int fY);
	void checkBounds();
	void checkStage();
	void detectInput();
	void updatePos();
	//void changeColor();
	void correct();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	int stageLength = 400;
	int stageHeight = 20;
	int boxSize = 5;
	int x = (gfx.ScreenWidth - stageLength) / 2 + (stageLength / 4);
	int y = (gfx.ScreenHeight - stageHeight) / 2 - boxSize - 1;
	int vx = 0;
	int vy = 0;
	int gb = 255;
	bool shapeIsChanged = false;
	bool inhibitUp;
	bool inhibitDown;
	bool inhibitLeft;
	bool inhibitRight;
	bool colliding;
	int valleyLeft = 200;
	int valleyRight = 400;
	/********************************/
};