#ifndef _MAP_
#define _MAP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Settings.h"
#include "SDLHandler.h"
#include "Tile.h"
#include "Dot.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int TOTAL_TILE_SPRITES = 3;
const int TILE_1 = 1;
const int TILE_2 = 2;
const int TILE_3 = 3;

class Map{
private:
	int x = 15;
	int y = 75;
	int rows,columns;
	Dot dot;
	std::vector<std::vector<int>> map;
	std::vector<Tile> tileSet;

	SDLHandler mapHandler;
	SDL_Texture* textura;
    SDL_Renderer* winRenderer;
	SDL_Rect gTileClips[ TOTAL_TILE_SPRITES];
	SDL_Rect camera = { x, y, 320, 240 };

	void load();
	void close();
	bool checkCollision( SDL_Rect a, SDL_Rect b );
public:
	Map();	
    void pollEvent(SDL_Event &evento);    
	void init(Settings &set, SDL_Renderer* renderer);
	void render();
	void update();	
	~Map();
};

#endif
