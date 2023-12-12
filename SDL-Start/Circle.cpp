#include "Circle.h"
#include <vector>

Circle::Circle() : hasReflected(false)
{
	circlePosX = rand() % 800 + 200;
	circlePosY = rand() % 500 + 300;
	circlePosXfloat = (float)circlePosX;
	circlePosYfloat = (float)circlePosY;
	circleVelX = (rand() % 11 - 5) / 30.0f;
	circleVelY = (rand() % 11 - 5) / 30.0f;
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
}

void Circle::checkCollision(int index, int textureWidth, int textureHeight, Circle balls[], int numberOfBalls, Camera camera)
{
	if (circlePosX > 1000) {
		int x = 0;
	}
	if (circlePosX + textureWidth / 2 >= camera.camera.w + camera.camera.x && circleVelX > 0)
	{
		//std::cout << "X wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelX *= -1;
	}

	if (circlePosY + textureHeight / 2 >= camera.camera.h + camera.camera.y && circleVelY > 0)
	{
		//std::cout << "Y wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelY *= -1;
	}
	//
	if (circlePosX - textureWidth / 2 <= camera.camera.x && circleVelX < 0)
	{
		//std::cout << "X wall collision " << circlePosX << ", " << circlePosY << std::endl;
		circleVelX *= -1;
	}

	if (circlePosY - textureHeight / 2 <= camera.camera.y && circleVelY < 0)
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
		if (sqrt(pow((circlePosXfloat - balls[i].circlePosXfloat), 2) + pow((circlePosYfloat - balls[i].circlePosYfloat), 2)) < (float)textureWidth)

		{
			if (index != i)
			{
				float left = sqrt(pow((circlePosXfloat - balls[i].circlePosXfloat), 2) + pow((circlePosYfloat - balls[i].circlePosYfloat), 2));
				float right = (float)textureWidth;
				//std::cout << "COLLISION" << std::endl;
				if (separation)
				{
					int x = 0;
					separate(balls[i], textureWidth);
				}
				else if (ballCollision)
				{
					reflection(balls[i], textureWidth);
				}
				float left2 = sqrt(pow((circlePosXfloat - balls[i].circlePosXfloat), 2) + pow((circlePosYfloat - balls[i].circlePosYfloat), 2));
				float right2 = (float)textureWidth;
				int y = 0;
			}

		}
		else
		{
			// Set the reflection flag for both circles
			hasReflected = false;
			balls[i].hasReflected = false;
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
	if (vNorm == 0)
	{
		separation_x = 0;
		separation_y = 0;
	}
	else
	{
		separation_x = (v[0]) / vNorm * (diameter - vNorm);
		separation_y = (v[1]) / vNorm * (diameter - vNorm);
	}

	float tmpx = separation_x * 0.5;
	float tmpy = separation_y * 0.5;


	circlePosXfloat = circlePosXfloat + tmpx;
	ball.circlePosXfloat = ball.circlePosXfloat - tmpx;
	circlePosYfloat = circlePosYfloat + tmpy;
	ball.circlePosYfloat = ball.circlePosYfloat - tmpy;

	if (ballCollision)
	{
		reflection(ball, diameter, separation_x, separation_y, v);
	}
}

void Circle::reflection(Circle& ball, int diameter, float separation_x, float separation_y, std::vector <float> v)
{
	float dotProduct = separation_x * getCircleVelX() + separation_y * getCircleVelY();

	if (dotProduct > 0) 
	{
		float tmpX = 2 * dotProduct * separation_x;
		float tmpY = 2 * dotProduct * separation_y;

		// Scale down the adjustment to avoid a sudden increase in speed
		//tmpX *= 0.5;
		//tmpY *= 0.5;

		setCircleVelX(getCircleVelX() - tmpX);
		ball.setCircleVelX(ball.getCircleVelX() + tmpX);

		setCircleVelY(getCircleVelY() - tmpY);
		ball.setCircleVelY(ball.getCircleVelY() + tmpY);
	}
}

void Circle::reflection(Circle ball, int diameter)
{
	std::vector <float> v;
	v.push_back(circlePosX - ball.getCirclePosX());
	v.push_back(circlePosY - ball.getCirclePosY());
	float vNorm = sqrt(pow(v[0], 2) + pow(v[1], 2));

	float separation_x, separation_y;
	if (vNorm == 0)
	{
		separation_x = 0;
		separation_y = 0;
	}
	else
	{
		separation_x = (v[0]) / vNorm * (diameter - vNorm);
		separation_y = (v[1]) / vNorm * (diameter - vNorm);
	}

	float dotProduct = separation_x * getCircleVelX() + separation_y * getCircleVelY();

	//if (dotProduct > 0) 
	{
		float tmpX = 2 * dotProduct * separation_x;
		float tmpY = 2 * dotProduct * separation_y;

		// Scale down the adjustment to avoid a sudden increase in speed
		//tmpX *= 0.5;
		//tmpY *= 0.5;

		setCircleVelX(getCircleVelX() - tmpX);
		ball.setCircleVelX(ball.getCircleVelX() + tmpX);

		setCircleVelY(getCircleVelY() - tmpY);
		ball.setCircleVelY(ball.getCircleVelY() + tmpY);
	}
}
