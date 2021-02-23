#ifndef _MAP_
#define _MAP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <map>
#include "Settings.h"
#include "Defines.h"
#include "SDLHandler.h"
#include "Tile.h"
#include "TextHandler.h"
#include "yaml-cpp/yaml.h"

const int OFFSET_X = 200;
const int OFFSET_Y = 40;
const int OPTION_ROW = 6;
const int OPTION_COL = 6;
const int default_null_tile = TYPE_WALL_1;
const int default_tile = TYPE_NULL;

class Map{
	private:
	SDL_Point clickOffset;
	int x = 12;
	int y = 10;	
	float scaleX,scaleY;
	float xRelative, yRelative;        		
	int rows,columns;
	int players;
	int playersPendings;
	bool canExit = false;
	
	std::vector<std::vector<int>> map;
	std::vector<Tile> tileSet;
	std::map<int, Tile> opt;
	std::map<int, int> types;
	std::string name;
	
	TTF_Font* font = NULL;
	Tile selected;
	SDLHandler mapHandler;	
    SDL_Renderer* winRenderer;
	TextHandler textPlayerHandler;
	SDL_Rect camera = { x, y, 160, 144 };
	
	SDL_Color white = {255, 255, 255};
	SDL_Color yellow = {255, 204, 0};

	//Initicializa el mapa con los tiles pre cargados
	void load();
	//Initicializa el mapa con los tiles de opciones
	void load_objectTiles();

	void renderMap();
	void renderOptionsMap();
	void renderSelected();

	void changeSelected();
	void putTileMap();
	void updateClick();
	void updateModel();
	int getTypebyFilCol(int _fil, int _col);
	void createNewMap(int,int,int);
	void openfromfile(std::string _path,std::string &_file);
	void fillTypes();
public:
	Map();
	void setRenderer(SDL_Renderer *_renderer)	;
    void pollEvent(SDL_Event &evento);    
	void init(Settings &set, std::string &_name,int _maxplayer, bool create);
	void setResolution(int,int);
	std::vector<std::vector<int>> getMap() const;
	std::string getMapName() const;
	bool getCanExit() const;
	void render();
	void update();	
	~Map();
};

#endif
