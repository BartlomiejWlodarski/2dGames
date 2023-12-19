#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Tile.h"

class Player1
{
private:
	int player1Size;
	int player1Width;
	int player1Height;
	int player1PosX;
	int player1PosY;

	float player1VelX;
	float player1VelY;
	const float player1VelStep = 0.5;
	const float smooth = 0.5;


	
	bool up;
	bool down;
	bool left;
	bool right;

public:
	Player1(int levelWidth, int levelHeight, int startX, int startY, int textureWidth, int textureHeight);
	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;
	int tilesX;
	int tilesY;
	int score = 0;
	int width;
	int height;
	float posX;
	float posY;
	int getPlayer1Size();
	void setPlayer1Size(int value);
	int getPlayer1Width();
	void setPlayer1Width(int value);
	int getPlayer1Height();
	void setPlayer1Height(int value);
	int getPlayer1PosX();
	void setPlayer1PosX(int value);
	int getPlayer1PosY();
	void setPlayer1PosY(int value);
	float getPlayer1VelX();
	void setPlayer1VelX(float value);
	float getPlayer1VelY();
	void setPlayer1VelY(float value);
	void movePlayer1(int stopX, int stopY, std::vector <Tile*> tiles);
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
};

