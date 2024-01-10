#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Tile.h"

class Player2
{
private:
	int player2Size;
	int player2Width;
	int player2Height;
	int player2PosX;
	int player2PosY;

	float player2VelX;
	float player2VelY;
	const float player2VelStep = 0.5;
	const float smooth = 0.5;



	bool up;
	bool down;
	bool left;
	bool right;

	float h = 250;
	float t = 2;

	bool jumpPressed = false;
	bool jumping = false;
	
	float v0;
	float vx = player2VelStep / 1;
	float xh = 260;
	float g = - 2 * h * pow(vx, 2) / pow(xh, 2);
	int jumps = 0;
	int jumpLimit = 1;
	//float g = 0;

public:
	Player2(int levelWidth, int levelHeight, int startX, int startY, int textureWidth, int textureHeight);
	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;
	int tilesX;
	int tilesY;
	int score = 0;
	int width;
	int height;
	float posX;
	float posY;
	int fallOption = 0;
	int getPlayer2Size();
	void setPlayer2Size(int value);
	int getPlayer2Width();
	void setPlayer2Width(int value);
	int getPlayer2Height();
	void setPlayer2Height(int value);
	int getPlayer2PosX();
	void setPlayer2PosX(int value);
	int getPlayer2PosY();
	void setPlayer2PosY(int value);
	float getPlayer2VelX();
	void setPlayer2VelX(float value);
	float getPlayer2VelY();
	void setPlayer2VelY(float value);
	void movePlayer2(int stopX, int stopY, std::vector <Tile*> tiles);
	void playerKeyPressed(SDL_Keycode sym);
	void playerKeyReleased(SDL_Keycode sym);
	void checkCameraWindow(int stopX, int stopY);
	void findCollidableTiles(std::vector <Tile*> tiles);
	void checkTileCollision(std::vector <Tile*> tiles, int index);
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	float clamp(float x, float min, float max);
	void jump();
	void jumpSecondPhase();
	void gravitation();
	bool signChangePositiveToNegative(float oldValue, float newValue);
	void afterFall();
	void changeJumpParameters();
};

