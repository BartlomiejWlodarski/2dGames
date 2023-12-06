#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Camera.h"
#include <vector>

class Circle
{
private:
	int circlePosX;
	int circlePosY;

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

	bool separation;
	bool ballCollision;

public:
	float circlePosXfloat;
	float circlePosYfloat;

	Circle();
	int getCirclePosX();
	void setCirclePosX(int value);
	int getCirclePosY();
	void setCirclePosY(int value);
	float getCircleVelX();
	void setCircleVelX(float value);
	float getCircleVelY();
	void setCircleVelY(float value);
	int getCircleDesX();
	void setCircleDesX(int value);
	int getCircleDesY();
	void setCircleDesY(int value);
	bool getSeparation();
	void setSeparation(bool value);
	bool getBallCollision();
	void setBallCollision(bool value);
	float roundToUpper(float a);
	void moveCircle(int index, int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera, std::vector <float> *result, int *indexResult);
	void checkCollision(int index, int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera, std::vector <float>* result, int* indexResult);
	void screenEdgeCollision();
	void circlesCollision();
	void checkCameraWindow(int stopX, int stopY);
	void separate(Circle ball, int diameter, std::vector <float>* result);
	void reflection(Circle ball, int diameter, float separation_x, float separation_y, std::vector <float> v, std::vector <float> *result);
	void reflection(Circle ball, int diameter);
};
