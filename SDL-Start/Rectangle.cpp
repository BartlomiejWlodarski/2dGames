#include "Rectangle.h"
#include <vector>

Rectangle::Rectangle(){}

Rectangle::Rectangle(int width, int height)
{
	l = rand() % 800 + 200;
	t = rand() % 500 + 300;
	w = width;
	h = height;
	rectangleVelX = (rand() % 11 - 5) / 30.0f;
	rectangleVelY = (rand() % 11 - 5) / 30.0f;
}

float Rectangle::r() {
	return l + w;
}

float Rectangle::b() {
	return t + h;
}


float Rectangle::roundToUpper(float a)
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

void Rectangle::moveRectangle(int index, Rectangle balls[], int numberOfBalls, Camera camera)
{

	l += rectangleVelX;
	t += rectangleVelY;
	checkCollision(index, balls, numberOfBalls, camera);
}

void Rectangle::checkCollision(int index, Rectangle balls[], int numberOfBalls, Camera camera)
{
	if (r() >= camera.camera.w + camera.camera.x && rectangleVelX > 0)
	{
		//std::cout << "X wall collision " << rectanglePosX << ", " << rectanglePosY << std::endl;
		rectangleVelX *= -1;
	}

	if (b() >= camera.camera.h + camera.camera.y && rectangleVelY > 0)
	{
		//std::cout << "Y wall collision " << rectanglePosX << ", " << rectanglePosY << std::endl;
		rectangleVelY *= -1;
	}
	//
	if (l <= camera.camera.x && rectangleVelX < 0)
	{
		//std::cout << "X wall collision " << rectanglePosX << ", " << rectanglePosY << std::endl;
		rectangleVelX *= -1;
	}

	if (t <= camera.camera.y && rectangleVelY < 0)
	{
		//std::cout << "Y wall collision " << rectanglePosX << ", " << rectanglePosY << std::endl;
		rectangleVelY *= -1;
	}

	/*for (int i = 0; i < numberOfBalls; i++)
	{
		std::cout << balls[i].rectanglePosX << ", " << balls[i].rectanglePosY << std::endl;
	}*/

	//for (int i = 0; i < numberOfBalls; i++)
	//{
	//	//if (abs(rectanglePosX - balls[i].getRectanglePosX()) < textureWidth && abs(rectanglePosY - balls[i].getRectanglePosY()) < textureHeight && i != index)
	//	if (sqrt(pow((rectanglePosXfloat - balls[i].rectanglePosXfloat), 2) + pow((rectanglePosYfloat - balls[i].rectanglePosYfloat), 2)) < (float)textureWidth)

	//	{
	//		if (index != i)
	//		{
	//			float left = sqrt(pow((rectanglePosXfloat - balls[i].rectanglePosXfloat), 2) + pow((rectanglePosYfloat - balls[i].rectanglePosYfloat), 2));
	//			float right = (float)textureWidth;
	//			//std::cout << "COLLISION" << std::endl;
	//			if (separation)
	//			{
	//				int x = 0;
	//				separate(balls[i], textureWidth);
	//			}
	//			else if (ballCollision)
	//			{
	//				reflection(balls[i], textureWidth);
	//			}
	//			float left2 = sqrt(pow((rectanglePosXfloat - balls[i].rectanglePosXfloat), 2) + pow((rectanglePosYfloat - balls[i].rectanglePosYfloat), 2));
	//			float right2 = (float)textureWidth;
	//			int y = 0;
	//		}

	//	}
	//	else
	//	{
	//		// Set the reflection flag for both rectangles
	//		hasReflected = false;
	//		balls[i].hasReflected = false;
	//	}
	//}

}

void Rectangle::screenEdgeCollision()
{
}

void Rectangle::rectanglesCollision()
{
}


void Rectangle::separate(Rectangle& ball, int diameter)
{
	/*std::vector <float> v;
	v.push_back(rectanglePosX - ball.getRectanglePosX());
	v.push_back(rectanglePosY - ball.getRectanglePosY());
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


	rectanglePosXfloat = rectanglePosXfloat + tmpx;
	ball.rectanglePosXfloat = ball.rectanglePosXfloat - tmpx;
	rectanglePosYfloat = rectanglePosYfloat + tmpy;
	ball.rectanglePosYfloat = ball.rectanglePosYfloat - tmpy;

	if (ballCollision)
	{
		reflection(ball, diameter, separation_x, separation_y, v);
	}*/
}

void Rectangle::reflection(Rectangle& ball, int diameter, float separation_x, float separation_y, std::vector <float> v)
{
	//float dotProduct = separation_x * getRectangleVelX() + separation_y * getRectangleVelY();

	//if (dotProduct > 0)
	//{
	//	float tmpX = 2 * dotProduct * separation_x;
	//	float tmpY = 2 * dotProduct * separation_y;

	//	// Scale down the adjustment to avoid a sudden increase in speed
	//	//tmpX *= 0.5;
	//	//tmpY *= 0.5;

	//	setRectangleVelX(getRectangleVelX() - tmpX);
	//	ball.setRectangleVelX(ball.getRectangleVelX() + tmpX);

	//	setRectangleVelY(getRectangleVelY() - tmpY);
	//	ball.setRectangleVelY(ball.getRectangleVelY() + tmpY);
	//}
}

void Rectangle::reflection(Rectangle ball, int diameter)
{
	//std::vector <float> v;
	//v.push_back(rectanglePosX - ball.getRectanglePosX());
	//v.push_back(rectanglePosY - ball.getRectanglePosY());
	//float vNorm = sqrt(pow(v[0], 2) + pow(v[1], 2));

	//float separation_x, separation_y;
	//if (vNorm == 0)
	//{
	//	separation_x = 0;
	//	separation_y = 0;
	//}
	//else
	//{
	//	separation_x = (v[0]) / vNorm * (diameter - vNorm);
	//	separation_y = (v[1]) / vNorm * (diameter - vNorm);
	//}

	//float dotProduct = separation_x * getRectangleVelX() + separation_y * getRectangleVelY();

	////if (dotProduct > 0) 
	//{
	//	float tmpX = 2 * dotProduct * separation_x;
	//	float tmpY = 2 * dotProduct * separation_y;

	//	// Scale down the adjustment to avoid a sudden increase in speed
	//	//tmpX *= 0.5;
	//	//tmpY *= 0.5;

	//	setRectangleVelX(getRectangleVelX() - tmpX);
	//	ball.setRectangleVelX(ball.getRectangleVelX() + tmpX);

	//	setRectangleVelY(getRectangleVelY() - tmpY);
	//	ball.setRectangleVelY(ball.getRectangleVelY() + tmpY);
	//}
}
