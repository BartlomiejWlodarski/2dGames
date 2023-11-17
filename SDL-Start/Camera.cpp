#include "Camera.h"

Camera::Camera(int x, int y, int screen_w, int screen_h)
{
	camera = { x, y, screen_w, screen_h };
	SCREEN_WIDTH = screen_w;
	SCREEN_HEIGHT = screen_h;
}

void Camera::positionLockEdgeSnappingCamera(int playerX, int playerY)
{
	//Center the camera over the dot
	camera.x = (playerX) - SCREEN_WIDTH / 2;
	camera.y = (playerY) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Camera::positionLockCameraWindow(int playerX, int playerY)
{
	//Lock the horizontal camera
	camera.x = (playerX) - SCREEN_WIDTH / 2;

	//Camera window vertically
	if (playerY < camLineY1 + camera.y)
	{
		camera.y += playerY - (camLineY1 + camera.y);
	}

	if (playerY > camLineY2 + camera.y)
	{
		camera.y += playerY - (camLineY2 + camera.y);
	}
}

void Camera::twoPlayersCameraWindow(int p1X, int p1Y, int p2X, int p2Y, int p2width, int p2height)
{

	stopPlayer1X = 0;
	stopPlayer1Y = 0;
	stopPlayer2X = 0;
	stopPlayer2Y = 0;

	//Camera window horizontally
	if (p1X < camWindowX1 + camera.x && p2X + p2width < camWindowX2 + camera.x)
	{
		camera.x += p1X - (camWindowX1 + camera.x);
	}
	else if (p1X < camWindowX1 + camera.x && p2X + p2width >= camWindowX2 + camera.x)
	{
		stopPlayer1X = 1;
	}

	if (p1X > camWindowX2 + camera.x && p2X > camWindowX1 + camera.x)
	{
		camera.x += p1X - (camWindowX2 + camera.x);
	}
	else if (p1X > camWindowX2 + camera.x && p2X <= camWindowX1 + camera.x)
	{
		stopPlayer1X = -1;
	}

	//Camera window vertically
	if (p1Y < camWindowY1 + camera.y && p2Y + p2height < camWindowY2 + camera.y)
	{
		camera.y += p1Y - (camWindowY1 + camera.y);
	}
	else if (p1Y < camWindowY1 + camera.y && p2Y + p2height >= camWindowY2 + camera.y)
	{
		stopPlayer1Y = 1;
	}

	if (p1Y > camWindowY2 + camera.y && p2Y > camWindowY1 + camera.y)
	{
		camera.y += p1Y - (camWindowY2 + camera.y);
	}
	else if (p1Y > camWindowY2 + camera.y && p2Y <= camWindowY1 + camera.y)
	{
		stopPlayer1Y = -1;
	}

	//Camera window horizontally
	if (p2X < camWindowX1 + camera.x && p1X < camWindowX2 + camera.x)
	{
		camera.x += p2X - (camWindowX1 + camera.x);
	}
	else if (p2X < camWindowX1 + camera.x && p1X >= camWindowX2 + camera.x)
	{
		stopPlayer2X = 1;
	}

	if (p2X + p2width > camWindowX2 + camera.x && p1X > camWindowX1 + camera.x)
	{
		camera.x += p2X + p2width - (camWindowX2 + camera.x);
	}
	else if (p2X + p2width > camWindowX2 + camera.x && p1X <= camWindowX1 + camera.x)
	{
		stopPlayer2X = -1;
	}
	//Camera window vertically
	if (p2Y < camWindowY1 + camera.y && p1Y < camWindowY2 + camera.y)
	{
		camera.y += p2Y - (camWindowY1 + camera.y);
	}
	else if (p2Y < camWindowY1 + camera.y && p1Y >= camWindowY2 + camera.y)
	{
		stopPlayer2Y = 1;
	}

	if (p2Y + p2height > camWindowY2 + camera.y && p1Y > camWindowY1 + camera.y)
	{
		camera.y += p2Y + p2height - (camWindowY2 + camera.y);
	}
	else if (p2Y + p2height > camWindowY2 + camera.y && p1Y <= camWindowY1 + camera.y)
	{
		stopPlayer2Y = -1;
	}
}
