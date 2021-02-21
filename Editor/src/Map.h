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
#include "yaml-cpp/yaml.h"

const int OFFSET_X = 200;
const int OFFSET_Y = 70;
const int OPTION_ROW = 6;
const int OPTION_COL = 6;
const int default_null_tile = 403;

class Map{
	private:
	SDL_Point clickOffset;
	int x = 12;
	int y = 10;	
	float scaleX,scaleY;
	float xRelative, yRelative;        		
	int rows,columns;
	int players;
	
	std::vector<std::vector<int>> map;
	std::vector<Tile> tileSet;
	std::map<int, Tile> opt;
	std::string name;
	
	TTF_Font* font = NULL;
	Tile selected;
	SDLHandler mapHandler;	
    SDL_Renderer* winRenderer;
	SDL_Rect camera = { x, y, 160, 144 };

	//Initicializa el mapa con los tiles pre cargados
	void load();
	//Initicializa el mapa con los tiles de opciones
	void load_objectTiles();

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
	void createNewMap(int, int);
	void openfromfile(std::string _path,std::string &_file);
public:
	Map();
	void setRenderer(SDL_Renderer *_renderer)	;
    void pollEvent(SDL_Event &evento);    
	void init(Settings &set, std::string &_name, bool create);
	void setResolution(int,int);
	std::vector<std::vector<int>> getMap() const;
	std::string getMapName() const;
	void render();
	void update();	
	~Map();
};

#endif
