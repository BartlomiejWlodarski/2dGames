#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

#include "LTexture.h"

using namespace std;

class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType, int TILE_WIDTH, int TILE_HEIGHT);

	//Shows the tile
	void render(SDL_Renderer* gRenderer, LTexture gTileTexture, SDL_Rect gTileClips[]);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};