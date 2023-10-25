#include "Circle.h"

Circle::Circle(int levelWidth, int levelHeight, int startX, int startY)
{
	this->circlePosX = startX;
	this->circlePosY = startY;
	this->circleVelX = 0;
	this->circleVelY = 0;
	this->circleDesX = this->circlePosX;
	this->circleDesY = this->circlePosY;
	this->LEVEL_WIDTH = levelWidth;
	this->LEVEL_HEIGHT = levelHeight;
}

int Circle::getCirclePosX()
{
	return this->circlePosX;
}

void Circle::setCirclePosX(int value)
{
	this->circlePosX = value;
}

int Circle::getCirclePosY()
{
	return this->circlePosY;
}

void Circle::setCirclePosY(int value)
{
	this->circlePosY = value;
}

int Circle::getCircleVelX()
{
	return this->circleVelX;
}

void Circle::setCircleVelX(int value)
{
	this->circleVelX = value;
}

int Circle::getCircleVelY()
{
	return this->circleVelY;
}

void Circle::setCircleVelY(int value)
{
	this->circleVelY = value;
}

int Circle::getCircleDesX()
{
	return this->circleDesX;
}

void Circle::setCircleDesX(int value)
{
	this->circleDesX = value;
}

int Circle::getCircleDesY()
{
	return this->circleDesY;
}

void Circle::setCircleDesY(int value)
{
	this->circleDesY = value;
}

float Circle::roundToUpper(float a)
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

void Circle::moveCircle(int textureWidth, int textureHeight)
{
	if (abs(circlePosX - circleDesX) > abs(circleVelStepX)) {
		circlePosX += (int)circleVelStepX;
	}

	if ((circlePosX - textureWidth / 2 < 0) || (circlePosX + textureWidth/2 > LEVEL_WIDTH))
	{
		//Move back
		circlePosX -= (int)circleVelStepX;
	}

	if (abs(circlePosY - circleDesY) > abs(circleVelStepY)) {
		circlePosY += (int)circleVelStepY;
	}

	if ((circlePosY - textureHeight / 2 < 0) || (circlePosY + textureHeight/2 > LEVEL_HEIGHT))
	{
		//Move back
		circlePosY -= (int)circleVelStepY;
	}
}

void Circle::playerKeyPressed(int textureWidth, int textureHeight, int camX, int camY)
{
	SDL_GetMouseState(&circleDesX, &circleDesY);
	circleDesX += camX;	
	circleDesY += camY;
	/*circleDesX -= textureWidth / 2;
	circleDesY -= textureHeight / 2;*/
	circleVelStepX = (float)((float)(circleDesX - circlePosX) / 200);
	circleVelStepX = roundToUpper(circleVelStepX);
	circleVelStepY = (float)((float)(circleDesY - circlePosY) / 200);
	circleVelStepY = roundToUpper(circleVelStepY);
	std::cout << "Mouse clicked at position: x - " << circleDesX << "; y - " << circleDesY << "\n";
}

