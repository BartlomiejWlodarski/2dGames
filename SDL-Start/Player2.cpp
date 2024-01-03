#include "Player2.h"

Player2::Player2(int levelWidth, int levelHeight, int startX, int startY, int textureWidth, int textureHeight)
{
	this->player2PosX = startX;
	this->player2PosY = startY;
	posX = float(getPlayer2PosX());
	posY = float(getPlayer2PosY());
	this->player2VelX = 0;
	this->player2VelY = 0;

	this->LEVEL_WIDTH = levelWidth;
	this->LEVEL_HEIGHT = levelHeight;

	this->player2Size = LEVEL_HEIGHT / 10;



	width = textureWidth;
	height = textureHeight;
}

int Player2::getPlayer2Size()
{
	return this->player2Size;
}

void Player2::setPlayer2Size(int value)
{
	this->player2Size = value;
}

int Player2::getPlayer2Width()
{
	return this->player2Width;
}

void Player2::setPlayer2Width(int value)
{
	width = value;
	this->player2Width = value;
}

int Player2::getPlayer2Height()
{
	return this->player2Height;
}

void Player2::setPlayer2Height(int value)
{
	height = value;
	this->player2Height = value;
}

int Player2::getPlayer2PosX()
{
	return this->player2PosX;
}

void Player2::setPlayer2PosX(int value)
{
	posX = value;
	this->player2PosX = value;
}

int Player2::getPlayer2PosY()
{
	return this->player2PosY;
}

void Player2::setPlayer2PosY(int value)
{
	posY = value;
	this->player2PosY = value;
}

float Player2::getPlayer2VelX()
{
	return this->player2VelX;
}

void Player2::setPlayer2VelX(float value)
{
	this->player2VelX = value;
}

float Player2::getPlayer2VelY()
{
	return this->player2VelY;
}

void Player2::setPlayer2VelY(float value)
{
	this->player2VelY = value;
}

void Player2::movePlayer2(int stopX, int stopY, std::vector <Tile*> tiles)
{
	if (signChangePositiveToNegative(player2VelY, player2VelY - g))
	{
		jumpSecondPhase();
	}
	player2VelY -= g;
	
	//checkCameraWindow(stopX, stopY);
	//Move the dot left or right
	posX += player2VelX;


	//If the dot went too far to the left or right
	if ((posX - width / 2 < 0) || (posX + width / 2 > LEVEL_WIDTH))
	{
		//Move back
		posX -= player2VelX;
	}

	player2PosX = int(posX);

	//Move the dot up or down
	posY += player2VelY;


	//If the dot went too far up or down
	if ((posY - height / 2 < 0) || (posY + height / 2 > LEVEL_HEIGHT))
	{
		//Move back
		posY -= player2VelY;
	}

	player2PosY = int(posY);
	findCollidableTiles(tiles);
}

void Player2::playerKeyPressed(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP: player2VelY -= (player2VelStep * (1 - smooth)) + (player2VelY * smooth);
		//std::cout << "Up arrow pressed" << "\n";
		up = true;
		break;
	case SDLK_DOWN: player2VelY += (player2VelStep * (1 - smooth)) + (player2VelY * smooth);
		//std::cout << "Down arrow pressed" << "\n";
		down = true;
		break;
	case SDLK_LEFT: player2VelX -= (player2VelStep * (1 - smooth)) + (player2VelX * smooth);
		//std::cout << "Left arrow pressed" << "\n";
		left = true;
		break;
	case SDLK_RIGHT: player2VelX += (player2VelStep * (1 - smooth)) + (player2VelX * smooth);
		//std::cout << "Right arrow pressed" << "\n";
		right = true;
		break;
	case SDLK_LCTRL: 
		fallOption++;
		fallOption = fallOption % 3;

		if (fallOption == 0)
		{
			cout << "Normal fall" << endl;
		}
		else if (fallOption == 1)
		{
			cout << "Quick fall" << endl;
		}
		else if (fallOption == 2)
		{
			cout << "Double jump" << endl;
		}
		break;
	case SDLK_SPACE: 
		if (!jumping)
		{
			jumping = true;
			jump();
		}

		break;
	}
}

void Player2::playerKeyReleased(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP: player2VelY = 0;
		//std::cout << "Up arrow released" << "\n";
		up = false;
		break;
	case SDLK_DOWN: player2VelY = 0;
		//std::cout << "Down arrow released" << "\n";
		down = false;
		break;
	case SDLK_LEFT: player2VelX = 0;
		//std::cout << "Left arrow released" << "\n";
		left = false;
		break;
	case SDLK_RIGHT: player2VelX = 0;
		//std::cout << "Right arrow released" << "\n";
		right = false;
		break;
	case SDLK_SPACE: 
		if (jumping)
			afterFall();
		jumping = false;
		break;
	}
}

void Player2::checkCameraWindow(int stopX, int stopY)
{
	if (stopY == 1 && up)
	{
		player2VelY = 0;
	}
	if (stopY == -1 && down)
	{
		player2VelY = 0;
	}
	if (stopX == 1 && left)
	{
		player2VelX = 0;
	}
	if (stopX == -1 && right)
	{
		player2VelX = 0;
	}
}

void Player2::findCollidableTiles(std::vector<Tile*> tiles)
{
	int col = int(player2PosX / 80);
	int row = int(player2PosY / 80);
	int index;

	// Function finds 3x3 square of tiles surrounding player and if a tile is water checks collision
	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
		{
			index = row * tilesX + col + tilesX * (i - 1) + (j - 1);
			if (index >= 0 && index < tilesX * tilesY && index >= row * tilesX + tilesX * (i - 1) && index < (row + 1) * tilesX + tilesX * (i - 1))
			{
				// If tile is water
				if (tiles[index]->getType() > 2)
				{
					checkTileCollision(tiles, index);
				}
			}
		}
	}
}

float Player2::getLeft()
{
	return float(posX - width * 0.5);
}

float Player2::getRight()
{
	return float(posX + width * 0.5);
}

float Player2::getTop()
{
	return float(posY - height * 0.5);
}

float Player2::getBottom()
{
	return float(posY + height * 0.5);
}

float Player2::clamp(float x, float min, float max)
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

void Player2::jump()
{
	if (jumps < jumpLimit)
	{
		v0 = 2 * h * (vx) / xh;
		player2VelY = -v0;
		jumps++;
		jumpLimit = 1;
		cout << "g = " << g << endl;
		cout << "v0 = " << v0 << endl;
	}
}

void Player2::jumpSecondPhase()
{
	jumping = false;
	switch (fallOption)
	{
	case 0:
		
		break;
	case 1:
		g = 3 * g;
		break;
	case 2:
		jumpLimit = 2;

	}
	cout << "Fall " << endl;
	cout << "g = " << g << endl;
}

void Player2::afterFall()
{
	player2VelY = 0;
	g = -2 * h * pow(vx, 2) / pow(xh, 2);
	jumps = 0;
	
}

bool Player2::signChangePositiveToNegative(float oldValue, float newValue)
{
	//if ((oldValue > 0 && newValue > 0) || (oldValue < 0 && newValue < 0))
	//	return false;
	//else
	//	return true;

	if (oldValue < 0 && newValue > 0)
		return true;
	else
		return false;
}



void Player2::gravitation()
{
	player2VelY -= g;
}



void Player2::checkTileCollision(std::vector<Tile*> tiles, int index)
{
	float left = getRight() - tiles[index]->getLeft();
	float right = tiles[index]->getRight() - getLeft();
	float top = getBottom() - tiles[index]->getTop();
	float bottom = tiles[index]->getBottom() - getTop();


	if (left > 0 && right > 0 && top > 0 && bottom > 0)
	{
		float separationX;
		float separationY;
		left < right ? separationX = -left : separationX = right;
		top < bottom ? separationY = -top : separationY = bottom;

		if (abs(separationX) < abs(separationY))
		{
			 separationY = 0;
		}
		else if (abs(separationX) > abs(separationY))
		{
			separationX = 0;
		}
		if (separationY < 0 )
		{
			afterFall();
		}
		else if (separationY > 0 && posX < getRight() && posX > getLeft())
		{
			afterFall();
		}
		posX += separationX;
		posY += separationY;
	}

}

