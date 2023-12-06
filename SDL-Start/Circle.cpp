#include "Circle.h"
#include <vector>

Circle::Circle() : hasReflected(false)
{
	circlePosX = rand()%800+200;
	circlePosY = rand()%500+300;
	circlePosXfloat = (float)circlePosX;
	circlePosYfloat = (float)circlePosY;
	circleVelX = (rand() % 11 - 5) / 20.0f;
	circleVelY = (rand() % 11 - 5) / 20.0f;
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

float Circle::getCircleVelX()
{
	return this->circleVelX;
}

void Circle::setCircleVelX(float value)
{
	this->circleVelX = value;
}

float Circle::getCircleVelY()
{
	return this->circleVelY;
}

void Circle::setCircleVelY(float value)
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
	
	circlePosXfloat += circleVelX;
	circlePosYfloat += circleVelY;
	circlePosX = (int)circlePosXfloat;
	circlePosY = (int)circlePosYfloat;
	checkCollision(index, textureWidth, textureHeight, balls, numberOfBalls, camera);
	hasReflected = false;
}

void Circle::checkCollision(int index, int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera)
{
	if (circlePosX + textureWidth/2 == camera.camera.w + camera.camera.x)
	{
		//std::cout << "X wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelX *= -1;
	}

	if (circlePosY + textureHeight / 2 == camera.camera.h + camera.camera.y)
	{
		//std::cout << "Y wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelY *= -1;
	}
	//
	if (circlePosX - textureWidth / 2 == camera.camera.x)
	{
		//std::cout << "X wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelX *= -1;
	}

	if (circlePosY - textureHeight / 2 == camera.camera.y)
	{
		//std::cout << "Y wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelY *= -1;
	}
	
	/*for (int i = 0; i < numberOfBalls; i++)
	{
		std::cout << balls[i].circlePosX << ", " << balls[i].circlePosY << std::endl;
	}*/

	for (int i = 0; i < numberOfBalls; i++)
	{
		//if (abs(circlePosX - balls[i].getCirclePosX()) < textureWidth && abs(circlePosY - balls[i].getCirclePosY()) < textureHeight && i != index)
		if (sqrt(float(pow((circlePosX - balls[i].getCirclePosX()), 2) + pow((circlePosY - balls[i].getCirclePosY()), 2))) < (float)textureWidth  && i != index)

		{
			float left = sqrt(float(pow((circlePosX - balls[i].getCirclePosX()), 2) + pow((circlePosY - balls[i].getCirclePosY()), 2)));
			float right = (float)textureWidth;
			//std::cout << "COLLISION" << std::endl;
			if (separation)
			{
				separate(balls[i], textureWidth);
			}
			else if (ballCollision)
			{
				reflection(balls[i], textureWidth);
			}
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

void Circle::separate(Circle& ball, int diameter)
{
	std::vector <float> v;
	v.push_back(circlePosX - ball.getCirclePosX());
	v.push_back(circlePosY - ball.getCirclePosY());
	float vNorm = sqrt(pow(v[0], 2) + pow(v[1], 2));

	float separation_x, separation_y;
	separation_x = (v[0]) / vNorm * (diameter - vNorm);
	separation_y = (v[1]) / vNorm * (diameter - vNorm);

	if (abs(separation_x) > 2 || (separation_y) > 2) {
		//std::cout << "SEPARATE" << std::endl;
		//std::cout << separation_x <<", " << separation_y << std::endl;
	}

	int tmpx = int(abs(separation_x) * 0.5);
	int tmpy = int(abs(separation_y) * 0.5);
	if (v[0] > 0)
	{
		setCirclePosX(getCirclePosX() + int(abs(separation_x) * 0.5));
		ball.setCirclePosX(ball.getCirclePosX() - int(abs(separation_x) * 0.5));
	}
	else {
		setCirclePosX(getCirclePosX() - int(abs(separation_x) * 0.5));
		ball.setCirclePosX(ball.getCirclePosX() + int(abs(separation_x) * 0.5));
	}

	if (v[1] > 0)
	{
		setCirclePosY(getCirclePosY() + abs(separation_y) * 0.5);
		ball.setCirclePosY(ball.getCirclePosY() - abs(separation_y) * 0.5);
	}
	else {
		setCirclePosY(getCirclePosY() - abs(separation_y) * 0.5);
		ball.setCirclePosY(ball.getCirclePosY() + abs(separation_y) * 0.5);
	}
	if (ballCollision)
	{
		reflection(ball, diameter, separation_x, separation_y, v);
	}
}

void Circle::reflection(Circle& ball, int diameter, float separation_x, float separation_y, std::vector <float> v)
{
	if (!hasReflected && !ball.hasReflected) 
	{
		float dotProduct = separation_x * float(getCircleVelX()) + separation_y * float(getCircleVelY());
		//setCircleVelX(getCircleVelX() - 2 * dotProduct * separation_x);
		//setCircleVelY(getCircleVelY() - 2 * dotProduct * separation_y);
		//ball.setCircleVelX(ball.getCircleVelX() - 2 * dotProduct * separation_x);
		//ball.setCircleVelY(ball.getCircleVelY() - 2 * dotProduct * separation_y);
		float tmpX = abs(2 * dotProduct * separation_x);
		float tmpY = abs(2 * dotProduct * separation_y);

		if (v[0] > 0)
		{
			setCircleVelX(getCircleVelX() + tmpX);
			ball.setCircleVelX(ball.getCircleVelX() - tmpX);
		}
		else {
			setCircleVelX(getCircleVelX() - tmpX);
			ball.setCircleVelX(ball.getCircleVelX() + tmpX);
		}

		if (v[1] > 0)
		{
			setCircleVelY(getCircleVelY() - tmpY);
			ball.setCircleVelY(ball.getCircleVelY() + tmpY);
		}
		else {
			setCircleVelY(getCircleVelY() + tmpY);
			ball.setCircleVelY(ball.getCircleVelY() - tmpY);
		}

		// Set the reflection flag for both circles
		hasReflected = true;
		ball.hasReflected = true;
	}
	

}

void Circle::reflection(Circle ball, int diameter)
{
	std::vector <float> v;
	v.push_back(circlePosX - ball.getCirclePosX());
	v.push_back(circlePosY - ball.getCirclePosY());
	float vNorm = sqrt(pow(v[0], 2) + pow(v[1], 2));

	//float dotProduct = separation_x * float(getCircleVelX()) + separation_y * float(getCircleVelY());
	setCircleVelX(getCircleVelX() - 2 * getCircleVelX() * v[0] / vNorm);
	setCircleVelY(getCircleVelY() - 2 * getCircleVelY() * v[1] / vNorm);
	ball.setCircleVelX(ball.getCircleVelX() - 2 * ball.getCircleVelX() * v[0] / vNorm);
	ball.setCircleVelY(ball.getCircleVelY() - 2 * ball.getCircleVelY() * v[1] / vNorm);


	////float dotProduct = separation_x * float(getCircleVelX()) + separation_y * float(getCircleVelY());
	//setCircleVelX(getCircleVelX() + 2 * v[0] / vNorm);
	//setCircleVelY(getCircleVelY() + 2 * v[1] / vNorm);
	//ball.setCircleVelX(ball.getCircleVelX() - 2 * v[0] / vNorm);
	//ball.setCircleVelY(ball.getCircleVelY() - 2 * v[1] / vNorm);

	/*if (v[0] > 0)
	{
		setCirclePosX(getCirclePosX() + int(abs(separation_x) * 0.5));
		ball.setCirclePosX(ball.getCirclePosX() - int(abs(separation_x) * 0.5));
	}
	else {
		setCirclePosX(getCirclePosX() - int(abs(separation_x) * 0.5));
		ball.setCirclePosX(ball.getCirclePosX() + int(abs(separation_x) * 0.5));
	}

	if (v[1] > 0)
	{
		setCirclePosY(getCirclePosY() + abs(separation_y) * 0.5);
		ball.setCirclePosY(ball.getCirclePosY() - abs(separation_y) * 0.5);
	}
	else {
		setCirclePosY(getCirclePosY() - abs(separation_y) * 0.5);
		ball.setCirclePosY(ball.getCirclePosY() + abs(separation_y) * 0.5);
	}*/
}
