#include "Circle.h"


Circle::Circle()
{
	circlePosX = rand()%800+200;
	circlePosY = rand()%500+300;
	circlePosXfloat = (float)circlePosX;
	circlePosYfloat = (float)circlePosY;
	circleVelX = (rand() % 11 - 5) / 10.0f;
	circleVelY = (rand() % 11 - 5) / 10.0f;
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

bool Circle::getSeparation()
{
	return this->separation;
}

void Circle::setSeparation(bool value)
{
	this->separation = value;
}

bool Circle::getBallCollision()
{
	return this->ballCollision;
}

void Circle::setBallCollision(bool value)
{
	this->ballCollision = value;
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

void Circle::moveCircle(int index, int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera)
{
	checkCollision(index, textureWidth, textureHeight, balls, numberOfBalls, camera);
	circlePosXfloat += circleVelX;
	circlePosYfloat += circleVelY;
	circlePosX = (int)circlePosXfloat;
	circlePosY = (int)circlePosYfloat;
}

void Circle::checkCollision(int index, int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera)
{
	if (circlePosX + textureWidth/2 == camera.camera.w + camera.camera.x)
	{
		std::cout << "X wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelX *= -1;
	}

	if (circlePosY + textureHeight / 2 == camera.camera.h + camera.camera.y)
	{
		std::cout << "Y wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelY *= -1;
	}
	//
	if (circlePosX - textureWidth / 2 == camera.camera.x)
	{
		std::cout << "X wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelX *= -1;
	}

	if (circlePosY - textureHeight / 2 == camera.camera.y)
	{
		std::cout << "Y wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelY *= -1;
	}
	
	/*for (int i = 0; i < numberOfBalls; i++)
	{
		std::cout << balls[i].circlePosX << ", " << balls[i].circlePosY << std::endl;
	}*/

	for (int i = 0; i < numberOfBalls; i++)
	{
		if (abs(circlePosX - balls[i].getCirclePosX()) < textureWidth && abs(circlePosY - balls[i].getCirclePosY()) < textureHeight && i != index)
		{
			//std::cout << "COLLISION" << std::endl;
			if (separation)
			{
				separate(balls[i], textureWidth);
			}

			/*if (ballCollision)
			{
				reflection(balls[i], textureWidth);
			}*/
		}
	}

}

void Circle::screenEdgeCollision()
{
}

void Circle::circlesCollision()
{
}


void Circle::checkCameraWindow(int stopX, int stopY)
{
	if (stopY == 1 && up)
	{
		circleDesY = circlePosY;
	}
	else if (stopY == -1 && down)
	{
		circleDesY = circlePosY;
	}

	if (stopX == 1 && left)
	{
		circleDesX = circlePosX;
	}
	else if (stopX == -1 && right)
	{
		circleDesX = circlePosX;
	}
}

void Circle::separate(Circle ball, int diameter)
{
	float separation_x, separation_y;
	separation_x = (circlePosX - ball.getCirclePosX()) / abs(circlePosX - ball.getCirclePosX()) * (diameter - abs(circlePosX - ball.getCirclePosX()));
	separation_y = (circlePosY - ball.getCirclePosY()) / abs(circlePosY - ball.getCirclePosY()) * (diameter - abs(circlePosY - ball.getCirclePosY()));

	setCirclePosX(getCirclePosX() + separation_x * 0.5);
	setCirclePosY(getCirclePosY() + separation_y * 0.5);

	ball.setCirclePosX(getCirclePosX() - separation_x * 0.5);
	ball.setCirclePosY(getCirclePosY() - separation_y * 0.5);
}

void Circle::reflection(Circle ball, int diameter)
{

}
