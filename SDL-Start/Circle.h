#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>

class Circle
{
private:
	int circlePosX;
	int circlePosY;
	int circleVelX;
	int circleVelY;
	int circleDesX;
	int circleDesY;
	float circleVelStepX = 0;
	float circleVelStepY = 0;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

public:
	Circle(int screenWidth, int screenHeight, int startX, int startY);
	int getCirclePosX();
	void setCirclePosX(int value);
	int getCirclePosY();
	void setCirclePosY(int value);
	int getCircleVelX();
	void setCircleVelX(int value);
	int getCircleVelY();
	void setCircleVelY(int value);
	int getCircleDesX();
	void setCircleDesX(int value);
	int getCircleDesY();
	void setCircleDesY(int value);
	float roundToUpper(float a);
	void moveCircle(int textureWidth, int textureHeight);
	void playerKeyPressed(int textureWidth, int textureHeight);
};

