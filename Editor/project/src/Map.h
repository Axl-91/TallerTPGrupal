#ifndef _MAP_
#define _MAP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Settings.h"
#include "SDLHandler.h"
#include "Tile.h"

const int OFFSET_X = 200;
const int OFFSET_Y = 70;
const int OPTION_ROW = 6;
const int OPTION_COL = 6;

enum class Elements { wall = 11, door = 14, heal = 17, weapon =20, ammo = 21, enemy = 22, inmovable =29, treasure = 33, key = 35 };

class Map{
	private:
	int x = 15;
	int y = 70;
	int xRelative, yRelative;        		
	int rows,columns;
	
	std::vector<std::vector<int>> map;
	std::vector<Tile> tileSet;
	std::vector<Tile> tileOptions;
	
	TTF_Font* font = NULL;
	Tile selected;
	SDLHandler mapHandler;
	SDL_Texture* selectedTextura;
	SDL_Texture* textura;
    SDL_Renderer* winRenderer;
	SDL_Rect camera = { x, y, 160, 144 };

	//Initicializa el mapa con los tiles pre cargados
	void load();
	//Initicializa el mapa con los tiles de opciones
	void load_objectTiles();
	void initText();

	void renderMap();
	void renderOptionsMap();
	void renderSelected();

	void changeSelected();
	void putTileMap();
	void setCamera();
	void updateClick();
	bool checkCollision( SDL_Rect a, SDL_Rect b );
	void updateModel();
public:
	Map();	
    void pollEvent(SDL_Event &evento);    
	void init(Settings &set, SDL_Renderer* renderer);
	void render();
	void update();	
	~Map();
};

#endif
