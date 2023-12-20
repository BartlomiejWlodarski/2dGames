#include "Target.h"
#include <string>
#include "Vector.h"
#include <math.h>
# define M_PI           3.14159265358979323846


Target::Target(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
}

bool Target::playerWon(Player1 *p1, Player2 *p2)
{
	if (sqrt(pow(p1->getPlayer1PosX() - xPos, 2) + pow(p1->getPlayer1PosY() - yPos, 2)) < 40)
	{
		p1->score += 1;
		std::cout << "Player 1 found target!" << std::endl;
		return true;
	}
	else if (sqrt(pow(p2->getPlayer2PosX() - xPos, 2) + pow(p2->getPlayer2PosY() - yPos, 2)) < 40)
	{
		p2->score += 1;
		std::cout << "Player 2 found target!" << std::endl;
		return true;
	}
	
	return false;
}

float Target::clamp(float x, float min, float max)
{
	if (x <= min)
	{
		return min;
	}
	else if (x > min && x < max)
	{
		return x;
	}
	else
	{
		return max;
	}
}

void Target::updatePointer(Camera* camera, float scale)
{
	float fx = clamp(xPos, camera->camera.x * (1 / scale) + 50, camera->camera.x * (1 / scale) + camera->camera.w * (1 / scale) - 50);
	float fy = clamp(yPos, camera->camera.y * (1 / scale) + 50, camera->camera.y * (1 / scale) + camera->camera.h * (1 / scale) - 50);

	pointerX = fx;
	pointerY = fy;

	float midX = camera->camera.x + camera->camera.w * 0.5;
	float midY = camera->camera.y + camera->camera.h * 0.5;

	Vector v1 = { 100, 0, 0 };
	Vector v2 = { pointerX-midX, pointerY-midY, 0 };
	float angle = v1.angleBetweenVectors(v2);
	pointerAngle = angle / M_PI * 180;
	if (pointerY < midY)
	{
		pointerAngle = -abs(pointerAngle);
	}

}
