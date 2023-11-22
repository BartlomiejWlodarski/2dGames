#include "Player2.h"

Player2::Player2(int levelWidth, int levelHeight, int startX, int startY)
{
	this->player2PosX = startX;
	this->player2PosY = startY;
	this->player2VelX = 0;
	this->player2VelY = 0;
	this->player2DesX = this->player2PosX;
	this->player2DesY = this->player2PosY;
	this->LEVEL_WIDTH = levelWidth;
	this->LEVEL_HEIGHT = levelHeight;
}

int Player2::getPlayer2PosX()
{
	return this->player2PosX;
}

void Player2::setPlayer2PosX(int value)
{
	this->player2PosX = value;
}

int Player2::getPlayer2PosY()
{
	return this->player2PosY;
}

void Player2::setPlayer2PosY(int value)
{
	this->player2PosY = value;
}

int Player2::getPlayer2VelX()
{
	return this->player2VelX;
}

void Player2::setPlayer2VelX(int value)
{
	this->player2VelX = value;
}

int Player2::getPlayer2VelY()
{
	return this->player2VelY;
}

void Player2::setPlayer2VelY(int value)
{
	this->player2VelY = value;
}

int Player2::getPlayer2DesX()
{
	return this->player2DesX;
}

void Player2::setPlayer2DesX(int value)
{
	this->player2DesX = value;
}

int Player2::getPlayer2DesY()
{
	return this->player2DesY;
}

void Player2::setPlayer2DesY(int value)
{
	this->player2DesY = value;
}

float Player2::roundToUpper(float a)
{
	if (a < 0)
	{
		a -= 1;
	}
	else
	{
		a += 1;
	}
	return a;
}

void Player2::movePlayer2(int textureWidth, int textureHeight, int stopX, int stopY)
{
	checkCameraWindow(stopX, stopY);
	if (abs(player2PosX - player2DesX) > abs(player2VelStepX)) {
		player2PosX += (int)player2VelStepX;
	}
	
	if ((player2PosX - textureWidth / 2 < 0) || (player2PosX + textureWidth/2 > LEVEL_WIDTH))
	{
		//Move back
		player2PosX -= (int)player2VelStepX;
	}

	if (abs(player2PosY - player2DesY) > abs(player2VelStepY)) {
		player2PosY += (int)player2VelStepY;
	}

	if ((player2PosY - textureHeight / 2 < 0) || (player2PosY + textureHeight/2 > LEVEL_HEIGHT))
	{
		//Move back
		player2PosY -= (int)player2VelStepY;
	}
}

void Player2::playerKeyPressed(int textureWidth, int textureHeight, int camX, int camY, float scale)
{
	SDL_GetMouseState(&player2DesX, &player2DesY);
	if (scale < 1)
	{
		player2DesX *= 1 / scale;
		player2DesY *= 1 / scale;
	}

	player2DesX += camX;	
	player2DesY += camY;
	/*player2DesX -= textureWidth / 2;
	player2DesY -= textureHeight / 2;*/
	player2VelStepX = (float)((float)(player2DesX - player2PosX) / 200);
	player2VelStepX = roundToUpper(player2VelStepX);
	player2VelStepY = (float)((float)(player2DesY - player2PosY) / 200);
	player2VelStepY = roundToUpper(player2VelStepY);
	std::cout << "Mouse clicked at position: x - " << player2DesX << "; y - " << player2DesY << "\n";
	if (player2DesX - player2PosX > 0)
	{
		right = true;
		left = false;
	}
	else {
		right = false;
		left = true;
	}
	if (player2DesY - player2PosY > 0)
	{
		down = true;
		up = false;
	}
	else {
		down = false;
		up = true;
	}

}

void Player2::checkCameraWindow(int stopX, int stopY)
{
	if (stopY == 1 && up)
	{
		player2DesY = player2PosY;
	}
	else if (stopY == -1 && down)
	{
		player2DesY = player2PosY;
	}
	
	if (stopX == 1 && left)
	{
		player2DesX = player2PosX;
	}
	else if (stopX == -1 && right)
	{
		player2DesX = player2PosX;
	}
}

