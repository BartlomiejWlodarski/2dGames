#include "Player1.h"

Player1::Player1(int levelWidth, int levelHeight, int startX, int startY, int textureWidth, int textureHeight)
{
	this->player1PosX = startX;
	this->player1PosY = startY;
	posX = float(getPlayer1PosX());
	posY = float(getPlayer1PosY());
	this->player1VelX = 0;
	this->player1VelY = 0;

	this->LEVEL_WIDTH = levelWidth;
	this->LEVEL_HEIGHT = levelHeight;

	this->player1Size = LEVEL_HEIGHT / 10;

	tilesX = LEVEL_WIDTH / 80;
	tilesY = LEVEL_HEIGHT / 80;

	width = textureWidth;
	height = textureHeight;
}

int Player1::getPlayer1Size()
{
	return this->player1Size;
}

void Player1::setPlayer1Size(int value)
{
	this->player1Size = value;
}

int Player1::getPlayer1Width()
{
	return this->player1Width;
}

void Player1::setPlayer1Width(int value)
{
	this->player1Width = value;
}

int Player1::getPlayer1Height()
{
	return this->player1Height;
}

void Player1::setPlayer1Height(int value)
{
	this->player1Height = value;
}

int Player1::getPlayer1PosX()
{
	return this->player1PosX;
}

void Player1::setPlayer1PosX(int value)
{
	posX = value;
	this->player1PosX = value;
}

int Player1::getPlayer1PosY()
{
	return this->player1PosY;
}

void Player1::setPlayer1PosY(int value)
{
	posY = value;
	this->player1PosY = value;
}

float Player1::getPlayer1VelX()
{
	return this->player1VelX;
}

void Player1::setPlayer1VelX(float value)
{
	this->player1VelX = value;
}

float Player1::getPlayer1VelY()
{
	return this->player1VelY;
}

void Player1::setPlayer1VelY(float value)
{
	this->player1VelY = value;
}

void Player1::movePlayer1(int stopX, int stopY, std::vector <Tile*> tiles)
{
	//checkCameraWindow(stopX, stopY);
	//Move the dot left or right
	posX += player1VelX;
	

	//If the dot went too far to the left or right
	if ((posX - player1Height / 2 < 0) || (posX + player1Height / 2 > LEVEL_WIDTH))
	{
		//Move back
		posX -= player1VelX;
	}

	player1PosX = int(posX);

	//Move the dot up or down
	posY += player1VelY;
	

	//If the dot went too far up or down
	if ((posY - player1Height / 2 < 0) || (posY + player1Height / 2 > LEVEL_HEIGHT))
	{
		//Move back
		posY -= player1VelY;
	}

	player1PosY = int(posY);
	findCollidableTiles(tiles);
}

void Player1::playerKeyPressed(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_w: player1VelY -= (player1VelStep * (1 - smooth)) + (player1VelY * smooth);
		std::cout << "Up arrow pressed" << "\n";
		up = true;
		break;
	case SDLK_s: player1VelY += (player1VelStep * (1 - smooth)) + (player1VelY * smooth);
		std::cout << "Down arrow pressed" << "\n";
		down = true;
		break;
	case SDLK_a: player1VelX -= (player1VelStep * (1 - smooth)) + (player1VelX * smooth);
		std::cout << "Left arrow pressed" << "\n";
		left = true;
		break;
	case SDLK_d: player1VelX += (player1VelStep * (1 - smooth)) + (player1VelX * smooth);
		std::cout << "Right arrow pressed" << "\n";
		right = true;
		break;
	}
}

void Player1::playerKeyReleased(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_w: player1VelY = 0;
		std::cout << "Up arrow released" << "\n";
		up = false;
		break;
	case SDLK_s: player1VelY = 0;
		std::cout << "Down arrow released" << "\n";
		down = false;
		break;
	case SDLK_a: player1VelX = 0;
		std::cout << "Left arrow released" << "\n";
		left = false;
		break;
	case SDLK_d: player1VelX = 0;
		std::cout << "Right arrow released" << "\n";
		right = false;
		break;
	}
}

void Player1::checkCameraWindow(int stopX, int stopY)
{
	if (stopY == 1 && up)
	{
		player1VelY = 0;
	}
	if (stopY == -1 && down)
	{
		player1VelY = 0;
	}
	if (stopX == 1 && left)
	{
		player1VelX = 0;
	}
	if (stopX == -1 && right)
	{
		player1VelX = 0;
	}
}

void Player1::findCollidableTiles(std::vector<Tile*> tiles)
{
	int col = int(player1PosX / 80);
	int row = int(player1PosY / 80);
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

float Player1::getLeft()
{
	return float(posX-width*0.5);
}

float Player1::getRight()
{
	return float(posX + width * 0.5);
}

float Player1::getTop()
{
	return float(posY - width * 0.5);
}

float Player1::getBottom()
{
	return float(posY + width * 0.5);
}

float Player1::clamp(float x, float min, float max)
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

void Player1::checkTileCollision(std::vector<Tile*> tiles, int index)
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

		posX += separationX;
		posY += separationY;
	}

}

