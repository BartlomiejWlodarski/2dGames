#pragma once
#include "Player1.h"
#include "Player2.h"
#include "Camera.h"

class Target
{

public:
	int xPos;
	int yPos;
	float pointerX;
	float pointerY;
	float pointerAngle;
	Target(int x, int y);
	bool playerWon(Player1 *p1, Player2 *p2);
	float clamp(float x, float min, float max);
	void updatePointer(Camera *camera, float scale);

};

