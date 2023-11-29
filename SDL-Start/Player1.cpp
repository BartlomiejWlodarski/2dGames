#include "Player1.h"

Player1::Player1(int levelWidth, int levelHeight, int startX, int startY)
{
	this->player1PosX = startX;
	this->player1PosY = startY;
	this->player1VelX = 0;
	this->player1VelY = 0;

	this->LEVEL_WIDTH = levelWidth;
	this->LEVEL_HEIGHT = levelHeight;

	this->player1Size = LEVEL_HEIGHT / 10;
}

int Player1::getPlayer1Size()
{
	return this->player1Size;
}

void Player1::setPlayer1Size(int value)
{
	this->player1Size = value;
}

int Player1::getPlayer1Width()
{
	return this->player1Width;
}

void Player1::setPlayer1Width(int value)
{
	this->player1Width = value;
}

int Player1::getPlayer1Height()
{
	return this->player1Height;
}

void Player1::setPlayer1Height(int value)
{
	this->player1Height = value;
}

int Player1::getPlayer1PosX()
{
	return this->player1PosX;
}

void Player1::setPlayer1PosX(int value)
{
	this->player1PosX = value;
}

int Player1::getPlayer1PosY()
{
	return this->player1PosY;
}

void Player1::setPlayer1PosY(int value)
{
	this->player1PosY = value;
}

int Player1::getPlayer1VelX()
{
	return this->player1VelX;
}

void Player1::setPlayer1VelX(int value)
{
	this->player1VelX = value;
}

int Player1::getPlayer1VelY()
{
	return this->player1VelY;
}

void Player1::setPlayer1VelY(int value)
{
	this->player1VelY = value;
}

void Player1::movePlayer1(int stopX, int stopY)
{
	checkCameraWindow(stopX, stopY);
	//Move the dot left or right
	player1PosX += player1VelX;

	//If the dot went too far to the left or right
	if ((player1PosX - player1Width / 2 < 0) || (player1PosX + player1Width / 2 > LEVEL_WIDTH))
	{
		//Move back
		player1PosX -= player1VelX;
	}

	//Move the dot up or down
	player1PosY += player1VelY;

	//If the dot went too far up or down
	if ((player1PosY - player1Height / 2 < 0) || (player1PosY + player1Height / 2 > LEVEL_HEIGHT))
	{
		//Move back
		player1PosY -= player1VelY;
	}

}

void Player1::playerKeyPressed(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_w: player1VelY -= (player1VelStep * (1 - smooth)) + (player1VelY * smooth);
		std::cout << "Up arrow pressed" << "\n";
		up = true;
		break;
	case SDLK_s: player1VelY += (player1VelStep * (1 - smooth)) + (player1VelY * smooth);
		std::cout << "Down arrow pressed" << "\n";
		down = true;
		break;
	case SDLK_a: player1VelX -= (player1VelStep * (1 - smooth)) + (player1VelX * smooth);
		std::cout << "Left arrow pressed" << "\n";
		left = true;
		break;
	case SDLK_d: player1VelX += (player1VelStep * (1 - smooth)) + (player1VelX * smooth);
		std::cout << "Right arrow pressed" << "\n";
		right = true;
		break;
	}
}

void Player1::playerKeyReleased(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_w: player1VelY = 0;
		std::cout << "Up arrow released" << "\n";
		up = false;
		break;
	case SDLK_s: player1VelY = 0;
		std::cout << "Down arrow released" << "\n";
		down = false;
		break;
	case SDLK_a: player1VelX = 0;
		std::cout << "Left arrow released" << "\n";
		left = false;
		break;
	case SDLK_d: player1VelX = 0;
		std::cout << "Right arrow released" << "\n";
		right = false;
		break;
	}
}

void Player1::checkCameraWindow(int stopX, int stopY)
{
	if (stopY == 1 && up)
	{
		player1VelY = 0;
	}
	if (stopY == -1 && down)
	{
		player1VelY = 0;
	}
	if (stopX == 1 && left)
	{
		player1VelX = 0;
	}
	if (stopX == -1 && right)
	{
		player1VelX = 0;
	}
}

