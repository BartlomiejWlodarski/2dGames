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

int Tile::getLeft()
{
	return mBox.x;
}

int Tile::getRight()
{
	return mBox.x + mBox.w;
}

int Tile::getTop()
{
	return mBox.y;
}

int Tile::getBottom()
{
	return mBox.y + mBox.h;
}