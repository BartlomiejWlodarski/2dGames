#pragma once
#include <SDL.h>

class Camera
{
private:
	int SCREEN_WIDTH = 1040;
	int SCREEN_HEIGHT = 720;
	const int LEVEL_WIDTH = 1760;
	const int LEVEL_HEIGHT = 1440;

	const int camLineX1 = SCREEN_WIDTH / 2;
	const int camLineY1 = SCREEN_HEIGHT / 4;
	const int camLineX2 = SCREEN_WIDTH / 2;
	const int camLineY2 = SCREEN_HEIGHT * 3 / 4;

	const int camWindowX1 = SCREEN_WIDTH / 4;
	const int camWindowX2 = SCREEN_WIDTH * 6 / 8;
	const int camWindowY1 = SCREEN_HEIGHT / 4;
	const int camWindowY2 = SCREEN_HEIGHT * 6 / 8;

public:
	SDL_Rect camera;
	int stopPlayer1X;
	int stopPlayer1Y;
	int stopPlayer2X;
	int stopPlayer2Y;

	Camera(int x, int y, int screen_w, int screen_h);
	void positionLockEdgeSnappingCamera(int playerX, int playerY);
	void positionLockCameraWindow(int playerX, int playerY);
	void twoPlayersCameraWindow(int p1X, int p1Y, int p2X, int p2Y, int p2width, int p2height);


};

