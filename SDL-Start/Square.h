#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>

class Square
{
private:
	int squareSize;
	int squarePosX;
	int squarePosY;
	int squareVelX;
	int squareVelY;
	const int squareVelStep = 2;
	const float smooth = 0.5;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

public:
	Square(int screenWidth, int screenHeight, int startX, int startY);
	int getSquareSize();
	void setSquareSize(int value);
	int getSquarePosX();
	void setSquarePosX(int value);
	int getSquarePosY();
	void setSquarePosY(int value);
	int getSquareVelX();
	void setSquareVelX(int value);
	int getSquareVelY();
	void setSquareVelY(int value);
	void moveSquare();
	void playerKeyPressed(SDL_Keycode sym);
	void playerKeyReleased(SDL_Keycode sym);
};

