#pragma once
#include "Player1.h"
#include "Player2.h"

class Target
{

public:
	int xPos;
	int yPos;
	Target(int x, int y);
	bool playerWon(Player1 *p1, Player2 *p2);

};

