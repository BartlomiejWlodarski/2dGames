#include "Square.h"

Square::Square(int levelWidth, int levelHeight, int startX, int startY)
{
	this->squarePosX = startX;
	this->squarePosY = startY;
	this->squareVelX = 0;
	this->squareVelY = 0;

	this->LEVEL_WIDTH = levelWidth;
	this->LEVEL_HEIGHT = levelHeight;

	this->squareSize = LEVEL_HEIGHT / 10;
}

int Square::getSquareSize()
{
	return this->squareSize;
}

void Square::setSquareSize(int value)
{
	this->squareSize = value;
}

int Square::getPlayerWidth()
{
	return this->playerWidth;
}

void Square::setPlayerWidth(int value)
{
	this->playerWidth = value;
}

int Square::getPlayerHeight()
{
	return this->playerHeight;
}

void Square::setPlayerHeight(int value)
{
	this->playerHeight = value;
}

int Square::getSquarePosX()
{
	return this->squarePosX;
}

void Square::setSquarePosX(int value)
{
	this->squarePosX = value;
}

int Square::getSquarePosY()
{
	return this->squarePosY;
}

void Square::setSquarePosY(int value)
{
	this->squarePosY = value;
}

int Square::getSquareVelX()
{
	return this->squareVelX;
}

void Square::setSquareVelX(int value)
{
	this->squareVelX = value;
}

int Square::getSquareVelY()
{
	return this->squareVelY;
}

void Square::setSquareVelY(int value)
{
	this->squareVelY = value;
}

void Square::moveSquare(int stopX, int stopY)
{
	checkCameraWindow(stopX, stopY);
	//Move the dot left or right
	squarePosX += squareVelX;

	//If the dot went too far to the left or right
	if ((squarePosX < 0) || (squarePosX + squareSize > LEVEL_WIDTH))
	{
		//Move back
		squarePosX -= squareVelX;
	}

	//Move the dot up or down
	squarePosY += squareVelY;

	//If the dot went too far up or down
	if ((squarePosY < 0) || (squarePosY + squareSize > LEVEL_HEIGHT))
	{
		//Move back
		squarePosY -= squareVelY;
	}

}

void Square::playerKeyPressed(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP: squareVelY -= (squareVelStep * (1 - smooth)) + (squareVelY * smooth);
		std::cout << "Up arrow pressed" << "\n";
		up = true;
		break;
	case SDLK_DOWN: squareVelY += (squareVelStep * (1 - smooth)) + (squareVelY * smooth);
		std::cout << "Down arrow pressed" << "\n";
		down = true;
		break;
	case SDLK_LEFT: squareVelX -= (squareVelStep * (1 - smooth)) + (squareVelX * smooth);
		std::cout << "Left arrow pressed" << "\n";
		left = true;
		break;
	case SDLK_RIGHT: squareVelX += (squareVelStep * (1 - smooth)) + (squareVelX * smooth);
		std::cout << "Right arrow pressed" << "\n";
		right = true;
		break;
	}
}

void Square::playerKeyReleased(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP: squareVelY = 0;
		std::cout << "Up arrow released" << "\n";
		up = false;
		break;
	case SDLK_DOWN: squareVelY = 0;
		std::cout << "Down arrow released" << "\n";
		down = false;
		break;
	case SDLK_LEFT: squareVelX = 0;
		std::cout << "Left arrow released" << "\n";
		left = false;
		break;
	case SDLK_RIGHT: squareVelX = 0;
		std::cout << "Right arrow released" << "\n";
		right = false;
		break;
	}
}

void Square::checkCameraWindow(int stopX, int stopY)
{
	if (stopY == 1 && up)
	{
		squareVelY = 0;
	}
	if (stopY == -1 && down)
	{
		squareVelY = 0;
	}
	if (stopX == 1 && left)
	{
		squareVelX = 0;
	}
	if (stopX == -1 && right)
	{
		squareVelX = 0;
	}
}

