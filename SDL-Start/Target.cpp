#include "Target.h"
#include <string>

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
		std::cout << "Player 1 won, score: " << std::to_string(p1->score) << std::endl;
		return true;
	}
	else if (sqrt(pow(p2->getPlayer2PosX() - xPos, 2) + pow(p2->getPlayer2PosY() - yPos, 2)) < 40)
	{
		p2->score += 1;
		std::cout << "Player 2 won, score: " << std::to_string(p2->score) << std::endl;
		return true;
	}
	
	return false;
}
