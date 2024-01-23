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
#include "Player1.h"
#include "Player2.h"
#include "Camera.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Target.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <thread>

//Screen dimension constants
const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 720;

//Level dimension constants
int LEVEL_WIDTH = 8000;
int LEVEL_HEIGHT = 1280;

//Layer constants
const int LAYER2_WIDTH = 6400;
const int LAYER2_HEIGHT = 1280;
float layer2multiplier = 0.5;

//Tile constants
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TILE_WIDTH2 = 64;
const int TILE_HEIGHT2 = 64;
int TOTAL_TILES = 2500;
int TOTAL_TILES2 = 2000;
const int TOTAL_TILE_SPRITES = 9;
const int TOTAL_TILE_SPRITES2 = 9;

const int camLineX1 = SCREEN_WIDTH / 2;
const int camLineY1 = SCREEN_HEIGHT / 4;
const int camLineX2 = SCREEN_WIDTH / 2;
const int camLineY2 = SCREEN_HEIGHT * 3 / 4;

const int camWindowX1 = SCREEN_WIDTH / 4;
const int camWindowX2 = SCREEN_WIDTH * 6 / 8;
const int camWindowY1 = SCREEN_HEIGHT / 4;
const int camWindowY2 = SCREEN_HEIGHT * 6 / 8;

float scale = 1;

int cameraOption = 1;
bool separation = false;
bool ballCollision = false;

int currentLevel = 1;

//Tile* tileSet[TOTAL_TILES];
std::vector <Tile*> tileSet;
std::vector <Tile*> tileSet2;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Sets tiles from the map file
bool setTiles();
bool setTiles2();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

LTexture gPlayer2Texture;
LTexture gPlayer1Texture;
LTexture gTileTexture;
LTexture gTileTexture2;
LTexture gCircleTexture;
LTexture gTargetTexture;
LTexture gArrowTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
SDL_Rect gTileClips2[TOTAL_TILE_SPRITES2];

//Player1 constants and variables
Player1 player1(LEVEL_WIDTH, LEVEL_HEIGHT, 500, 500, gPlayer1Texture.getWidth(), gPlayer1Texture.getHeight());

//Player2 constants and variables
Player2 player2(LEVEL_WIDTH, LEVEL_HEIGHT, 600, 500, gPlayer2Texture.getWidth(), gPlayer2Texture.getHeight());

Target target(0, 0);

void renderTile(Tile* tile, SDL_Rect& camera)
{
	//Show the tile
	gTileTexture.render(gRenderer, tile->getBox().x - camera.x, tile->getBox().y - camera.y, &gTileClips[tile->getType()]);
}


void renderTile2(Tile* tile, SDL_Rect& camera)
{
	//Show the tile
	gTileTexture2.render(gRenderer, tile->getBox().x - (camera.x * layer2multiplier), tile->getBox().y - camera.y, &gTileClips2[tile->getType()]);
	//gTileTexture2.render(gRenderer, tile->getBox().x - (camera.x * layer2multiplier), tile->getBox().y - (camera.y * layer2multiplier) - (516 * layer2multiplier), &gTileClips2[tile->getType()]);
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

bool loadMedia(std::vector <Tile*> tiles)
{
	//Loading success flag
	bool success = true;

	//Load player2 texture
	if (!gPlayer2Texture.loadFromFile("textures/knight64x64.png", gRenderer))
	{
		printf("Failed to load player2 texture!\n");
		success = false;
	}

	gPlayer2Texture.setBlendMode(SDL_BLENDMODE_BLEND);
	//gPlayer2Texture.setAlpha(100);

	//Load player1 texture
	if (!gPlayer1Texture.loadFromFile("textures/sansUndertale.png", gRenderer))
	{
		printf("Failed to load player1 texture!\n");
		success = false;
	}
	gPlayer1Texture.setBlendMode(SDL_BLENDMODE_BLEND);
	//gPlayer1Texture.setAlpha(100);

	//Load circle texture
	if (!gCircleTexture.loadFromFile("textures/circleReduced.png", gRenderer))
	{
		printf("Failed to load circle texture!\n");
		success = false;
	}
	gCircleTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	//gPlayer1Texture.setAlpha(100);

	//Load target texture
	if (!gTargetTexture.loadFromFile("textures/chest.png", gRenderer))
	{
		printf("Failed to load target texture!\n");
		success = false;
	}
	gTargetTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	//gPlayer1Texture.setAlpha(100);

	//Load arrow texture
	if (!gArrowTexture.loadFromFile("textures/arrow.png", gRenderer))
	{
		printf("Failed to load arrow texture!\n");
		success = false;
	}
	gArrowTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	//gPlayer1Texture.setAlpha(100);

	if (!gTileTexture.loadFromFile("textures/assets64x64.png", gRenderer))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	if (!gTileTexture2.loadFromFile("textures/assets64x64.png", gRenderer))
	{
		printf("Failed to load assets texture!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles())
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles2())
	{
		printf("Failed to load assets tile set!\n");
		success = false;
	}
	return success;
}

void close(std::vector <Tile*> tiles, std::vector <Tile*> tiles2)
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

	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES2; ++i)
	{
		if (tiles2[i] != NULL)
		{
			delete tiles2[i];
			tiles2[i] = NULL;
		}
	}

	//Free loaded images
	gPlayer2Texture.free();
	gPlayer1Texture.free();
	gTileTexture.free();
	gTileTexture2.free();

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
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_TAB)
	{
		cameraOption += 1;
		cameraOption %= 4;
	}
	else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		player1.playerKeyPressed(e.key.keysym.sym);
		player2.playerKeyPressed(e.key.keysym.sym);
		//std::cout << "Player1PosX: " << player1PosX << "; Player1PosY: " << player1PosY << "; Player1VelX: " << player1VelX << "; Player1VelY: " << player1VelY << "\n";
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		player1.playerKeyReleased(e.key.keysym.sym);
		player2.playerKeyReleased(e.key.keysym.sym);
		//std::cout << "Player1PosX: " << player1PosX << "; Player1PosY: " << player1PosY << "; Player1VelX: " << player1VelX << "; Player1VelY: " << player1VelY << "\n";
	}
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
	{

		separation = !separation;
		std::cout << "Separation: " << to_string(separation) << "\n";
	}
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_o)
	{

		ballCollision = !ballCollision;
		std::cout << "Ball collision: " << to_string(ballCollision) << "\n";
	}

	//If mouse button was pressed
	//if (e.type == SDL_MOUSEBUTTONDOWN)
	//{
	//	
	//}


}

bool setTiles()
{
	// Update tile data
	Tile* tile = new Tile(0, 0, 0, 0, 0);
	//TOTAL_TILES = pow(16 + (currentLevel - 1) * 2, 2);
	//LEVEL_WIDTH = (16 + (currentLevel - 1) * 2) * 80;
	//LEVEL_HEIGHT = (16 + (currentLevel - 1) * 2) * 80;
	//TILES_IN_ONE_DIMENSION = (16 + (currentLevel - 1) * 2);

	player1.LEVEL_WIDTH = LEVEL_WIDTH;
	player1.LEVEL_HEIGHT = LEVEL_HEIGHT;
	player2.LEVEL_WIDTH = LEVEL_WIDTH;
	player2.LEVEL_HEIGHT = LEVEL_HEIGHT;

	player1.tilesX = LEVEL_WIDTH / TILE_WIDTH;
	player1.tilesY = LEVEL_HEIGHT / TILE_HEIGHT;
	player2.tilesX = LEVEL_WIDTH / TILE_WIDTH;
	player2.tilesY = LEVEL_HEIGHT / TILE_HEIGHT;

	for (int i = tileSet.size(); i < TOTAL_TILES; i++)
	{
		tileSet.push_back(tile);
	}
	delete tile;
	
	
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//string mapPath = "maps/labyrinth" + to_string(currentLevel) + ".map";
	string mapPath = "maps/z14.map";

	//Open the map
	std::ifstream map(mapPath);

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
				tileSet[i] = new Tile(x, y, tileType, TILE_WIDTH, TILE_HEIGHT);
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
			gTileClips[0].x = 0;
			gTileClips[0].y = 0;
			gTileClips[0].w = TILE_WIDTH2;
			gTileClips[0].h = TILE_HEIGHT2;

			gTileClips[1].x = 0;
			gTileClips[1].y = 64;
			gTileClips[1].w = TILE_WIDTH2;
			gTileClips[1].h = TILE_HEIGHT2;

			gTileClips[2].x = 0;
			gTileClips[2].y = 128;
			gTileClips[2].w = TILE_WIDTH2;
			gTileClips[2].h = TILE_HEIGHT2;

			gTileClips[3].x = 64;
			gTileClips[3].y = 0;
			gTileClips[3].w = TILE_WIDTH2;
			gTileClips[3].h = TILE_HEIGHT2;

			gTileClips[4].x = 64;
			gTileClips[4].y = 64;
			gTileClips[4].w = TILE_WIDTH2;
			gTileClips[4].h = TILE_HEIGHT2;

			gTileClips[5].x = 64;
			gTileClips[5].y = 128;
			gTileClips[5].w = TILE_WIDTH2;
			gTileClips[5].h = TILE_HEIGHT2;

			gTileClips[6].x = 128;
			gTileClips[6].y = 0;
			gTileClips[6].w = TILE_WIDTH2;
			gTileClips[6].h = TILE_HEIGHT2;

			gTileClips[7].x = 128;
			gTileClips[7].y = 64;
			gTileClips[7].w = TILE_WIDTH2;
			gTileClips[7].h = TILE_HEIGHT2;

			gTileClips[8].x = 160;
			gTileClips[8].y = 160;
			gTileClips[8].w = TILE_WIDTH2;
			gTileClips[8].h = TILE_HEIGHT2;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

bool setTiles2()
{
	// Update tile data
	Tile* tile = new Tile(0, 0, 0, 0, 0);


	for (int i = tileSet2.size(); i < TOTAL_TILES2; i++)
	{
		tileSet2.push_back(tile);
	}
	delete tile;


	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//string mapPath = "maps/labyrinth" + to_string(currentLevel) + ".map";
	string mapPath = "maps/z14layer2.map";

	//Open the map
	std::ifstream map(mapPath);

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES2; ++i)
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
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES2))
			{
				tileSet2[i] = new Tile(x, y, tileType, TILE_WIDTH2, TILE_HEIGHT2);
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
			x += TILE_WIDTH2;

			//If we've gone too far
			if (x >= LAYER2_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT2;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips2[0].x = 0;
			gTileClips2[0].y = 0;
			gTileClips2[0].w = TILE_WIDTH2;
			gTileClips2[0].h = TILE_HEIGHT2;

			gTileClips2[1].x = 0;
			gTileClips2[1].y = 64;
			gTileClips2[1].w = TILE_WIDTH2;
			gTileClips2[1].h = TILE_HEIGHT2;

			gTileClips2[2].x = 0;
			gTileClips2[2].y = 128;
			gTileClips2[2].w = TILE_WIDTH2;
			gTileClips2[2].h = TILE_HEIGHT2;

			gTileClips2[3].x = 64;
			gTileClips2[3].y = 0;
			gTileClips2[3].w = TILE_WIDTH2;
			gTileClips2[3].h = TILE_HEIGHT2;

			gTileClips2[4].x = 64;
			gTileClips2[4].y = 64;
			gTileClips2[4].w = TILE_WIDTH2;
			gTileClips2[4].h = TILE_HEIGHT2;

			gTileClips2[5].x = 64;
			gTileClips2[5].y = 128;
			gTileClips2[5].w = TILE_WIDTH2;
			gTileClips2[5].h = TILE_HEIGHT2;

			gTileClips2[6].x = 128;
			gTileClips2[6].y = 0;
			gTileClips2[6].w = TILE_WIDTH2;
			gTileClips2[6].h = TILE_HEIGHT2;

			gTileClips2[7].x = 128;
			gTileClips2[7].y = 64;
			gTileClips2[7].w = TILE_WIDTH2;
			gTileClips2[7].h = TILE_HEIGHT2;

			gTileClips2[8].x = 160;
			gTileClips2[8].y = 160;
			gTileClips2[8].w = TILE_WIDTH2;
			gTileClips2[8].h = TILE_HEIGHT2;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}


void cameraMenu(Camera* camera)
{
	switch (cameraOption)
	{
	case 0:
		scale = 1;
		camera->stopPlayer1X = 0;
		camera->stopPlayer1Y = 0;
		camera->stopPlayer2X = 0;
		camera->stopPlayer2Y = 0;
		camera->positionLockEdgeSnappingCamera(player2.getPlayer2PosX(), player2.getPlayer2PosY());
		break;
	case 1:
		camera->stopPlayer1X = 0;
		camera->stopPlayer1Y = 0;
		camera->stopPlayer2X = 0;
		camera->stopPlayer2Y = 0;
		camera->positionLockCameraWindow(player2.getPlayer2PosX(), player2.getPlayer2PosY());
		//Render line that allows to see the boundaries of camera in positionLockCameraWindow
		SDL_RenderDrawLine(gRenderer, camLineX1, camLineY1, camLineX2, camLineY2);
		break;
	case 2:
		camera->twoPlayersCameraWindow(player2.getPlayer2PosX(), player2.getPlayer2PosY(), player1.getPlayer1PosX(), player1.getPlayer1PosY());
		//Render line that allows to see the boundaries of camera in twoPlayersCameraWindow
		SDL_RenderDrawLine(gRenderer, camWindowX1, camWindowY1, camWindowX2, camWindowY1);
		SDL_RenderDrawLine(gRenderer, camWindowX2, camWindowY1, camWindowX2, camWindowY2);
		SDL_RenderDrawLine(gRenderer, camWindowX2, camWindowY2, camWindowX1, camWindowY2);
		SDL_RenderDrawLine(gRenderer, camWindowX1, camWindowY2, camWindowX1, camWindowY1);
		break;
	case 3:
		camera->stopPlayer1X = 0;
		camera->stopPlayer1Y = 0;
		camera->stopPlayer2X = 0;
		camera->stopPlayer2Y = 0;
		camera->centerCameraZoom(player1.getPlayer1PosX(), player1.getPlayer1PosY(), player2.getPlayer2PosX(), player2.getPlayer2PosY(), &scale);
		//Render line and center for center camera zoom				
		SDL_RenderDrawLine(gRenderer, player1.getPlayer1PosX() - camera->camera.x, player1.getPlayer1PosY() - camera->camera.y, player2.getPlayer2PosX() - camera->camera.x, player2.getPlayer2PosY() - camera->camera.y);
		SDL_RenderDrawLine(gRenderer, (camera->camera.w / 2 - 100) * (1 / scale), (camera->camera.h / 2) * (1 / scale), (camera->camera.w / 2 + 100) * (1 / scale), (camera->camera.h / 2) * (1 / scale));
		SDL_RenderDrawLine(gRenderer, (camera->camera.w / 2) * (1 / scale), (camera->camera.h / 2 - 100) * (1 / scale), (camera->camera.w / 2) * (1 / scale), (camera->camera.h / 2 + 100) * (1 / scale));
		break;
	}
}

void randomizeSpawnLocations(Player1* p1, Player2* p2, Target* t)
{
	bool success = false;
	int randomTile, randomTile2, randomTile3;
	while (!success)
	{
		randomTile = rand() % TOTAL_TILES;
		if (tileSet[randomTile]->getType() < 3)
		{
			p1->setPlayer1PosX(tileSet[randomTile]->getBox().x + 0.5 * tileSet[randomTile]->getBox().w);
			p1->setPlayer1PosY(tileSet[randomTile]->getBox().y + 0.5 * tileSet[randomTile]->getBox().h);
			success = true;
		}
	}

	success = false;
	while (!success)
	{
		//randomTile2 = rand() % TOTAL_TILES;
		randomTile2 = 130;
		if (tileSet[randomTile2]->getType() < 3 && randomTile2 != randomTile)
		{
			p2->setPlayer2PosX(tileSet[randomTile2]->getBox().x + 0.5 * tileSet[randomTile2]->getBox().w);
			p2->setPlayer2PosY(tileSet[randomTile2]->getBox().y + 0.5 * tileSet[randomTile2]->getBox().h);
			success = true;
		}
	}

	success = false;
	while (!success)
	{
		randomTile3 = rand() % TOTAL_TILES;
		if (tileSet[randomTile3]->getType() < 3 && randomTile3 != randomTile && randomTile3 != randomTile2)
		{
			t->xPos = (tileSet[randomTile3]->getBox().x + 0.5 * tileSet[randomTile3]->getBox().w);
			t->yPos = (tileSet[randomTile3]->getBox().y + 0.5 * tileSet[randomTile3]->getBox().h);
			success = true;
		}
	}
}


int main(int argc, char* args[])
{
	srand(time(0));
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		while (!quit) {
			//Load media
			if (!loadMedia(tileSet))
			{
				printf("Failed to load media!\n");
			}
			else
			{
				//Scale the player2 texture and update the position accordingly
				//gPlayer2Texture.setWidth(gPlayer2Texture.getWidth() * 5);
				//gPlayer2Texture.setHeight(gPlayer2Texture.getHeight() * 5);
				//player2.setPlayer2PosX(player2.getPlayer2PosX() + (gPlayer2Texture.getWidth() / 2));
				//player2.setPlayer2PosY(player2.getPlayer2PosY() + (gPlayer2Texture.getHeight() / 2));

				//Scale the player texture and update the position accordingly
				gPlayer1Texture.setWidth(gPlayer1Texture.getWidth() / 15);
				gPlayer1Texture.setHeight(gPlayer1Texture.getHeight() / 15);
				//player1.setPlayer1PosX(player2.getPlayer2PosX() + (gPlayer2Texture.getWidth() / 2));
				//player1.setPlayer1PosY(player2.getPlayer2PosY() + (gPlayer2Texture.getHeight() / 2));
				player1.setPlayer1Width(gPlayer1Texture.getWidth());
				player1.setPlayer1Height(gPlayer1Texture.getHeight());
				player2.setPlayer2Width(gPlayer2Texture.getWidth());
				player2.setPlayer2Height(gPlayer2Texture.getHeight());

				//Scale the target texture
				gTargetTexture.setWidth(gTargetTexture.getWidth() / 4);
				gTargetTexture.setHeight(gTargetTexture.getHeight() / 4);

				//Scale the circle texture and update the position accordingly
				gCircleTexture.setWidth(gPlayer1Texture.getHeight());
				gCircleTexture.setHeight(gPlayer1Texture.getHeight());


				randomizeSpawnLocations(&player1, &player2, &target);




				//Event handler
				SDL_Event e;

				//The camera area
				Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				//Reset vertical camera for positionLockCameraWindow
				camera.camera.y = (player2.getPlayer2PosY()) - SCREEN_HEIGHT / 2;

				//Reset vertical camera for twoPlayersCameraWindow
				camera.camera.x = (player2.getPlayer2PosX()) - SCREEN_WIDTH / 2;

				//Initialize balls
				Circle balls[15];
				int numberOfBalls = 15;
				for (int i = 0; i < numberOfBalls; i++)
				{
					balls[i] = Circle();
				}


				//balls[0].setCirclePosX(300);
				//balls[0].circlePosXfloat = 300;
				//balls[1].setCirclePosX(600);
				//balls[1].circlePosXfloat = 600;
				//balls[0].setCirclePosY(500);
				//balls[0].circlePosYfloat = 500;
				//balls[1].setCirclePosY(500);
				//balls[1].circlePosYfloat = 500;

				//balls[0].setCircleVelX(0.5);
				//balls[1].setCircleVelX(0.25);

				//balls[0].setCircleVelY(0);
				//balls[1].setCircleVelY(0);
				//
				//balls[1].setCircleVelY(0);

				//Initialize rects
				//Rectangle rects[5];
				//int numberOfRects = 5;
				//for (int i = 0; i < numberOfRects; i++)
				//{
				//	rects[i] = Rectangle(150, 100);
				//}

				//While application is running
				while (!(target.playerWon(&player1, &player2) || quit))
				{
					SDL_RenderSetScale(gRenderer, scale, scale);
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
					player1.movePlayer1(camera.stopPlayer1X, camera.stopPlayer1Y, tileSet);
					player2.movePlayer2(camera.stopPlayer2X, camera.stopPlayer2Y, tileSet);

					//for (int i = 0; i < numberOfBalls; i++)
					//{
					//	balls[i].setSeparation(separation);
					//	balls[i].setBallCollision(ballCollision);
					//	balls[i].moveCircle(i, gCircleTexture.getWidth(), gCircleTexture.getHeight(), balls, numberOfBalls, camera);
					//}

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0x4C, 0x40, 0x8E, 0xFF);
					SDL_RenderClear(gRenderer);

					
					//Render layer
					for (int i = 0; i < TOTAL_TILES2; ++i)
					{
						renderTile2(tileSet2[i], camera.camera);
					}
					
					//Render level
					for (int i = 0; i < TOTAL_TILES; ++i)
					{
						renderTile(tileSet[i], camera.camera);
					}

					//Render target
					gTargetTexture.render(gRenderer, target.xPos - (gTargetTexture.getWidth() / 2) - camera.camera.x, target.yPos - (gTargetTexture.getHeight() / 2) - camera.camera.y);

					gCircleTexture.render(gRenderer, player1.getPlayer1PosX() - (gCircleTexture.getWidth() / 2) - camera.camera.x, player1.getPlayer1PosY() - (gPlayer1Texture.getHeight() / 2) - camera.camera.y);

					//Render player1
					gPlayer1Texture.render(gRenderer, player1.getPlayer1PosX() - (gPlayer1Texture.getWidth() / 2) - camera.camera.x, player1.getPlayer1PosY() - (gPlayer1Texture.getHeight() / 2) - camera.camera.y);

					SDL_Rect fillRect = { player2.getPlayer2PosX() - (gPlayer2Texture.getWidth()/2) - camera.camera.x,  player2.getPlayer2PosY() - (gPlayer2Texture.getHeight()/2) - camera.camera.y,  gPlayer2Texture.getWidth(),  gPlayer2Texture.getHeight() };
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderDrawRect(gRenderer, &fillRect);

					//Render player2
					gPlayer2Texture.render(gRenderer, player2.getPlayer2PosX() - (gPlayer2Texture.getWidth() / 2) - camera.camera.x, player2.getPlayer2PosY() - (gPlayer2Texture.getHeight() / 2) - camera.camera.y);

					
					target.updatePointer(&camera, scale);

					if (target.xPos < camera.camera.x * (1/scale) || target.xPos > camera.camera.x + camera.camera.w * (1 / scale) || target.yPos < camera.camera.y * (1 / scale) || target.yPos > camera.camera.y + camera.camera.h * (1 / scale))
					{
						gArrowTexture.render(gRenderer, int(target.pointerX) - (gArrowTexture.getWidth() / 2) - camera.camera.x, int(target.pointerY) - (gArrowTexture.getHeight() / 2) - camera.camera.y, NULL, target.pointerAngle, NULL, SDL_FLIP_NONE);

					}

					

					//for (int i = 0; i < numberOfBalls; i++)
					//{
					//	gCircleTexture.render(gRenderer, balls[i].getCirclePosX() - (gCircleTexture.getWidth() / 2) - camera.camera.x, balls[i].getCirclePosY() - (gCircleTexture.getHeight() / 2) - camera.camera.y);
					//}


					//for (int i = 0; i < numberOfRects; i++)
					//{
					//	//rects[i].setSeparation(separation);
					//	//rects[i].setBallCollision(ballCollision);
					//	rects[i].moveRectangle(i, rects, numberOfRects, camera);
					//}

					//for (int i = 0; i < numberOfRects; i++)
					//{
					//	SDL_Rect fillRect = { rects[i].l - camera.camera.x,  rects[i].t - camera.camera.y,  rects[i].w,  rects[i].h };
					//	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					//	SDL_RenderFillRect(gRenderer, &fillRect);
					//}


					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					//Choosing which camera option to use
					cameraMenu(&camera);

					//Update screen
					SDL_RenderPresent(gRenderer);
				}
				currentLevel++;
				if (currentLevel > 3)
				{
					//quit = true;
					std::cout << "##################################################" << std::endl;
					std::cout << "Player 1 score: " << std::to_string(player1.score) << std::endl;
					std::cout << "Player 2 score: " << std::to_string(player2.score) << std::endl;
					std::cout << "##################################################" << std::endl;
					player1.score = 0;
					player2.score = 0;
					currentLevel = 1;
					std::this_thread::sleep_for(std::chrono::seconds(5));
				}
			}
		}


		

		//Free resources and close SDL
		close(tileSet, tileSet2);
	}
	return 0;
}
