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

void Square::moveSquare()
{
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
		break;
	case SDLK_DOWN: squareVelY += (squareVelStep * (1 - smooth)) + (squareVelY * smooth);
		std::cout << "Down arrow pressed" << "\n";
		break;
	case SDLK_LEFT: squareVelX -= (squareVelStep * (1 - smooth)) + (squareVelX * smooth);
		std::cout << "Left arrow pressed" << "\n";
		break;
	case SDLK_RIGHT: squareVelX += (squareVelStep * (1 - smooth)) + (squareVelX * smooth);
		std::cout << "Right arrow pressed" << "\n";
		break;
	}
}

void Square::playerKeyReleased(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP: squareVelY += (squareVelStep * (1 - smooth)) + (squareVelY * smooth);
		std::cout << "Up arrow released" << "\n";
		break;
	case SDLK_DOWN: squareVelY -= (squareVelStep * (1 - smooth)) + (squareVelY * smooth);
		std::cout << "Down arrow released" << "\n";
		break;
	case SDLK_LEFT: squareVelX += (squareVelStep * (1 - smooth)) + (squareVelX * smooth);
		std::cout << "Left arrow released" << "\n";
		break;
	case SDLK_RIGHT: squareVelX -= (squareVelStep * (1 - smooth)) + (squareVelX * smooth);
		std::cout << "Right arrow released" << "\n";
		break;
	}
}

