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
#include "Camera.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 720;

//Level dimension constants
const int LEVEL_WIDTH = 1760;
const int LEVEL_HEIGHT = 1440;

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 396;
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

const int camLineX1 = SCREEN_WIDTH / 2;
const int camLineY1 = SCREEN_HEIGHT / 4;
const int camLineX2 = SCREEN_WIDTH / 2;
const int camLineY2 = SCREEN_HEIGHT * 3 / 4;

const int camWindowX1 = SCREEN_WIDTH / 4;
const int camWindowX2 = SCREEN_WIDTH * 6 / 8;
const int camWindowY1 = SCREEN_HEIGHT / 4;
const int camWindowY2 = SCREEN_HEIGHT * 6 / 8;

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
LTexture gPlayerTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

//Square constants and variables
Square square(LEVEL_WIDTH, LEVEL_HEIGHT, 500, 500);

//Circle constants and variables
Circle circle(LEVEL_WIDTH, LEVEL_HEIGHT, 600, 500);

void renderTile(Tile* tile, SDL_Rect& camera)
{
	//Show the tile
	gTileTexture.render(gRenderer, tile->getBox().x - camera.x, tile->getBox().y - camera.y, &gTileClips[tile->getType()]);
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

	//Load player texture
	if (!gPlayerTexture.loadFromFile("textures/sansUndertale.png", gRenderer))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}
	gPlayerTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	//gPlayerTexture.setAlpha(100);

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
	gPlayerTexture.free();
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

void handleEvent(SDL_Event& e, int camX, int camY)
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
		circle.playerKeyPressed(gCircleTexture.getWidth(), gCircleTexture.getHeight(), camX, camY);
	}
}

bool setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("maps/map3.map");

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
			if (x >= LEVEL_WIDTH)
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
			//Scale the circle texture and update the position accordingly
			gCircleTexture.setWidth(gCircleTexture.getWidth() / 10);
			gCircleTexture.setHeight(gCircleTexture.getHeight() / 10);
			circle.setCirclePosX(circle.getCirclePosX() + (gCircleTexture.getWidth() / 2));
			circle.setCirclePosY(circle.getCirclePosY() + (gCircleTexture.getHeight() / 2));

			//Scale the player texture and update the position accordingly
			gPlayerTexture.setWidth(gCircleTexture.getWidth() / 3);
			gPlayerTexture.setHeight(gCircleTexture.getHeight() / 3);
			square.setSquarePosX(circle.getCirclePosX() + (gCircleTexture.getWidth() / 2));
			square.setSquarePosY(circle.getCirclePosY() + (gCircleTexture.getHeight() / 2));
			square.setPlayerWidth(gPlayerTexture.getWidth());
			square.setPlayerHeight(gPlayerTexture.getHeight());

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The camera area
			Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			//Reset vertical camera for positionLockCameraWindow
			camera.camera.y = (circle.getCirclePosY()) - SCREEN_HEIGHT / 2;

			//Reset vertical camera for twoPlayersCameraWindow
			camera.camera.x = (circle.getCirclePosX()) - SCREEN_WIDTH / 2;

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
					handleEvent(e, camera.camera.x, camera.camera.y);
				}
				
				//Move objects
				square.moveSquare(camera.stopPlayer2X, camera.stopPlayer2Y);
				circle.moveCircle(gCircleTexture.getWidth(), gCircleTexture.getHeight(), camera.stopPlayer1X, camera.stopPlayer1Y);

				//Choosing which camera option to use
				//camera.positionLockEdgeSnappingCamera(circle.getCirclePosX(), circle.getCirclePosY());
				//camera.positionLockCameraWindow(circle.getCirclePosX(), circle.getCirclePosY());
				camera.twoPlayersCameraWindow(circle.getCirclePosX(), circle.getCirclePosY(), square.getSquarePosX(), square.getSquarePosY(), square.getPlayerWidth(), square.getPlayerHeight());

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render level
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					renderTile(tileSet[i], camera.camera);
				}

				//Render square
				/*SDL_Rect fillRect = { square.getSquarePosX() - camera.camera.x, square.getSquarePosY() - camera.camera.y, square.getSquareSize(), square.getSquareSize()};
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);*/
				gPlayerTexture.render(gRenderer, square.getSquarePosX() - (gPlayerTexture.getWidth() / 2) - camera.camera.x, square.getSquarePosY() - (gPlayerTexture.getHeight() / 2) - camera.camera.y);

				//Render semi-translucent circle
				gCircleTexture.render(gRenderer, circle.getCirclePosX() - (gCircleTexture.getWidth() / 2) - camera.camera.x, circle.getCirclePosY() - (gCircleTexture.getHeight() / 2) - camera.camera.y);

				//Render square
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

				//Render line that allows to see the boundaries of camera in positionLockCameraWindow
				//SDL_RenderDrawLine(gRenderer, camLineX1, camLineY1, camLineX2, camLineY2);

				//Render rectangle that allows to see the boundaries of camera in twoPlayersCameraWindow
				//Render square
				

				//Render line that allows to see the boundaries of camera in positionLockCameraWindow
				SDL_RenderDrawLine(gRenderer, camWindowX1, camWindowY1, camWindowX2, camWindowY1);
				SDL_RenderDrawLine(gRenderer, camWindowX2, camWindowY1, camWindowX2, camWindowY2);
				SDL_RenderDrawLine(gRenderer, camWindowX2, camWindowY2, camWindowX1, camWindowY2);
				SDL_RenderDrawLine(gRenderer, camWindowX1, camWindowY2, camWindowX1, camWindowY1);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}

		//Free resources and close SDL
		close(tileSet);
	}
	return 0;
}
