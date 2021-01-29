#include "Map.h"

Map::Map(){}
/*
void Map::ver(int lvl[15][20]){
	for (int fil = 0; fil < 15; ++fil){
		for (int col = 0; col < 20; ++col){
			map[fil][col] = lvl[fil][col];
		}
	}
}
*/
void Map::render(){
	for (int fil = 0; fil < map.size(); ++fil){
		for (int col = 0; col < map[0].size(); ++col){
			int type = map[fil][col];
			if (type == 1){
				SDL_Rect bloque = {32*col+x, 32*fil+y, 31, 31};
				SDL_SetRenderDrawColor(winRenderer, 0x76, 0x76, 0x76, 0xFF);
				SDL_RenderFillRect(winRenderer, &bloque);     
			} else {
				SDL_Rect bloque = {32*col +x, 32*fil +y, 32, 32};
				SDL_SetRenderDrawColor(winRenderer, 0x0E, 0x24, 0x33, 0xFF);
				SDL_RenderFillRect(winRenderer, &bloque);
				bloque = {32*col+x, 32*fil+y, 31, 31};
				SDL_SetRenderDrawColor(winRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(winRenderer, &bloque);				
			}
		}
	}
}

void Map::init(std::vector<std::vector<int>>_map, SDL_Renderer* _renderer){	
	map = _map;
	winRenderer = _renderer;
	x = y = 160;
}

Map::~Map(){}
