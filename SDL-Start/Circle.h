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

	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;

public:
	Circle(int levelWidth, int levelHeight, int startX, int startY);
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
	void moveCircle(int textureWidth, int textureHeight, int stopCircleX, int stopCircleY);
	void playerKeyPressed(int textureWidth, int textureHeight, int camX, int camY, int* stopCircleX, int* stopCircleY);
};

