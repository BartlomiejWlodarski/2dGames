#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Camera.h"
#include <vector>

class Rectangle
{
private:
	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;

	bool up;
	bool down;
	bool left;
	bool right;

	

public:
	float l;
	float w;
	float t;
	float h;
	float rectangleVelX;
	float rectangleVelY;
	bool separation;
	bool ballCollision;


	Rectangle();
	Rectangle(int width, int height);
	float r();
	float b();
	float roundToUpper(float a);
	void moveRectangle(int index, Rectangle balls[], int numberOfBalls, Camera camera);
	void checkCollision(int index, Rectangle balls[], int numberOfBalls, Camera camera);
	void screenEdgeCollision();
	void rectanglesCollision();
	void separate(Rectangle& ball, int diameter);
	void reflection(Rectangle& ball, int diameter, float separation_x, float separation_y, std::vector <float> v);
	void reflection(Rectangle ball, int diameter);
};
