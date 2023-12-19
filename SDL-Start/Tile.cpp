#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

#include "Tile.h"
#include "LTexture.h"

using namespace std;

Tile::Tile(int x, int y, int tileType, int TILE_WIDTH, int TILE_HEIGHT)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}

void Tile::render(SDL_Renderer* gRenderer, LTexture gTileTexture, SDL_Rect gTileClips[])
{
	//Show the tile
	gTileTexture.render(gRenderer, mBox.x, mBox.y, &gTileClips[mType]);
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

float Tile::getLeft()
{
	return float(mBox.x);
}

float Tile::getRight()
{
	return float(mBox.x + mBox.w);
}

float Tile::getTop()
{
	return float(mBox.y);
}

float Tile::getBottom()
{
	return float(mBox.y + mBox.h);
}