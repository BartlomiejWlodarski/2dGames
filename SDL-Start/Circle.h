#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Camera.h"

class Circle
{
private:
	int circlePosX;
	int circlePosY;
	float circlePosXfloat;
	float circlePosYfloat;
	float circleVelX = 0.1;
	float circleVelY = 0.1;
	int circleDesX;
	int circleDesY;
	float circleVelStepX = 0;
	float circleVelStepY = 0;

	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;

	bool up;
	bool down;
	bool left;
	bool right;


public:
	Circle();
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
	void moveCircle(int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera);
	void checkCollision(int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera);
	void screenEdgeCollision();
	void circlesCollision();
	void checkCameraWindow(int stopX, int stopY);
};
