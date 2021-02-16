#ifndef _MAP_
#define _MAP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <map>
#include "Settings.h"
#include "SDLHandler.h"
#include "Tile.h"

const int OFFSET_X = 200;
const int OFFSET_Y = 70;
const int OPTION_ROW = 6;
const int OPTION_COL = 6;

class Map{
	private:
	SDL_Point clickOffset;
	int x = 15;
	int y = 70;	
	float scaleX,scaleY;
	float xRelative, yRelative;        		
	int rows,columns;
	
	std::vector<std::vector<int>> map;
	std::vector<Tile> tileSet;
	std::map<int, Tile> opt;
	
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
	int getTypebyFilCol(int _fil, int _col);
public:
	Map();	
    void pollEvent(SDL_Event &evento);    
	void init(Settings &set, SDL_Renderer *renderer);
	void setResolution(int,int);
	std::vector<std::vector<int>> getMap() const;
	void render();
	void update();	
	~Map();
};

#endif
