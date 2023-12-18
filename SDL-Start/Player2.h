#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>

class Player2
{
private:
	int player2PosX;
	int player2PosY;
	int player2VelX;
	int player2VelY;
	int player2DesX;
	int player2DesY;
	float player2VelStepX = 0;
	float player2VelStepY = 0;

	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;

	bool up;
	bool down;
	bool left;
	bool right;

public:
	Player2(int levelWidth, int levelHeight, int startX, int startY);
	int score = 0;
	int getPlayer2PosX();
	void setPlayer2PosX(int value);
	int getPlayer2PosY();
	void setPlayer2PosY(int value);
	int getPlayer2VelX();
	void setPlayer2VelX(int value);
	int getPlayer2VelY();
	void setPlayer2VelY(int value);
	int getPlayer2DesX();
	void setPlayer2DesX(int value);
	int getPlayer2DesY();
	void setPlayer2DesY(int value);
	float roundToUpper(float a);
	void movePlayer2(int textureWidth, int textureHeight, int stopX, int stopY);
	void playerKeyPressed(int textureWidth, int textureHeight, int camX, int camY, float scale);
	void checkCameraWindow(int stopX, int stopY);
};

