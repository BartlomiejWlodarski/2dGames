#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>

class Player1
{
private:
	int player1Size;
	int player1Width;
	int player1Height;
	int player1PosX;
	int player1PosY;
	int player1VelX;
	int player1VelY;
	const int player1VelStep = 2;
	const float smooth = 0.5;

	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;
	
	bool up;
	bool down;
	bool left;
	bool right;

public:
	Player1(int levelWidth, int levelHeight, int startX, int startY);
	int score = 0;
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
	int getPlayer1VelX();
	void setPlayer1VelX(int value);
	int getPlayer1VelY();
	void setPlayer1VelY(int value);
	void movePlayer1(int stopX, int stopY);
	void playerKeyPressed(SDL_Keycode sym);
	void playerKeyReleased(SDL_Keycode sym);
	void checkCameraWindow(int stopX, int stopY);
};

