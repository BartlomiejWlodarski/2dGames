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

	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;
	
	bool up;
	bool down;
	bool left;
	bool right;

public:
	Square(int levelWidth, int levelHeight, int startX, int startY);
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
	void moveSquare(int stopX, int stopY);
	void playerKeyPressed(SDL_Keycode sym);
	void playerKeyReleased(SDL_Keycode sym);
	void checkCameraWindow(int stopX, int stopY);
};

