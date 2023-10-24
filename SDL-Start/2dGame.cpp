//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

#include "LTexture.h"
#include "Tile.h"
#include "Square.h"
#include "Circle.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 720;

//Level dimension constants
const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 1200;

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 117;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_DIRT = 0;
const int TILE_GRASS = 1;
const int TILE_STONE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Sets tiles from the map file
bool setTiles(Tile* tiles[]);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

LTexture gCircleTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

//Square constants and variables
Square square(SCREEN_WIDTH, SCREEN_HEIGHT, 200, 200);

//Circle constants and variables
Circle circle(SCREEN_WIDTH, SCREEN_HEIGHT, 200, 200);

void renderTile(Tile* tile)
{
	//Show the tile
	gTileTexture.render(gRenderer, tile->getBox().x, tile->getBox().y, &gTileClips[tile->getType()]);
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("2d Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(Tile* tiles[])
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gCircleTexture.loadFromFile("textures/circlepng.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	gCircleTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	gCircleTexture.setAlpha(100);

	if (!gTileTexture.loadFromFile("textures/tiles.png", gRenderer))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}
	return success;
}

void close(Tile* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i] != NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	//Free loaded images
	gCircleTexture.free();
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		square.playerKeyPressed(e.key.keysym.sym);
		//std::cout << "SquarePosX: " << squarePosX << "; SquarePosY: " << squarePosY << "; SquareVelX: " << squareVelX << "; SquareVelY: " << squareVelY << "\n";
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		square.playerKeyReleased(e.key.keysym.sym);
		//std::cout << "SquarePosX: " << squarePosX << "; SquarePosY: " << squarePosY << "; SquareVelX: " << squareVelX << "; SquareVelY: " << squareVelY << "\n";
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		circle.playerKeyPressed(gCircleTexture.getWidth(), gCircleTexture.getHeight());
	}
}

bool setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("maps/map1.map");

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType, TILE_WIDTH, TILE_HEIGHT);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= SCREEN_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[TILE_DIRT].x = 0;
			gTileClips[TILE_DIRT].y = 0;
			gTileClips[TILE_DIRT].w = TILE_WIDTH;
			gTileClips[TILE_DIRT].h = TILE_HEIGHT;

			gTileClips[TILE_GRASS].x = 0;
			gTileClips[TILE_GRASS].y = 80;
			gTileClips[TILE_GRASS].w = TILE_WIDTH;
			gTileClips[TILE_GRASS].h = TILE_HEIGHT;

			gTileClips[TILE_STONE].x = 0;
			gTileClips[TILE_STONE].y = 160;
			gTileClips[TILE_STONE].w = TILE_WIDTH;
			gTileClips[TILE_STONE].h = TILE_HEIGHT;

			gTileClips[TILE_TOPLEFT].x = 80;
			gTileClips[TILE_TOPLEFT].y = 0;
			gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_LEFT].x = 80;
			gTileClips[TILE_LEFT].y = 80;
			gTileClips[TILE_LEFT].w = TILE_WIDTH;
			gTileClips[TILE_LEFT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMLEFT].x = 80;
			gTileClips[TILE_BOTTOMLEFT].y = 160;
			gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_TOP].x = 160;
			gTileClips[TILE_TOP].y = 0;
			gTileClips[TILE_TOP].w = TILE_WIDTH;
			gTileClips[TILE_TOP].h = TILE_HEIGHT;

			gTileClips[TILE_CENTER].x = 160;
			gTileClips[TILE_CENTER].y = 80;
			gTileClips[TILE_CENTER].w = TILE_WIDTH;
			gTileClips[TILE_CENTER].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOM].x = 160;
			gTileClips[TILE_BOTTOM].y = 160;
			gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

			gTileClips[TILE_TOPRIGHT].x = 240;
			gTileClips[TILE_TOPRIGHT].y = 0;
			gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_RIGHT].x = 240;
			gTileClips[TILE_RIGHT].y = 80;
			gTileClips[TILE_RIGHT].w = TILE_WIDTH;
			gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMRIGHT].x = 240;
			gTileClips[TILE_BOTTOMRIGHT].y = 160;
			gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

int main(int argc, char* args[])
{

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//The level tiles
		Tile* tileSet[TOTAL_TILES];

		//Load media
		if (!loadMedia(tileSet))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			gCircleTexture.setWidth(gCircleTexture.getWidth() / 10);
			gCircleTexture.setHeight(gCircleTexture.getHeight() / 10);
			circle.setCirclePosX(circle.getCirclePosX() + (gCircleTexture.getWidth() / 2));
			circle.setCirclePosY(circle.getCirclePosY() + (gCircleTexture.getHeight() / 2));
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					handleEvent(e);
				}
				square.moveSquare();


				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render level
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					renderTile(tileSet[i]);
				}

				//Render square
				SDL_Rect fillRect = { square.getSquarePosX(), square.getSquarePosY(), square.getSquareSize(), square.getSquareSize()};
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);

				//Render semi-translucent circle
				circle.moveCircle(gCircleTexture.getWidth(), gCircleTexture.getHeight());
				gCircleTexture.render(gRenderer, circle.getCirclePosX() - (gCircleTexture.getWidth() / 2), circle.getCirclePosY() - (gCircleTexture.getHeight() / 2));

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}

		//Free resources and close SDL
		close(tileSet);
	}
	return 0;
}
