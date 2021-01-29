#ifndef _MAP_
#define _MAP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Map{
private:
	int largo = 32;
	int ancho = 32;
	int x,y;
	std::vector<std::vector<int>> map;
	SDL_Texture* textura;
    SDL_Renderer* winRenderer;    
public:
	Map();	
	void init(std::vector<std::vector<int>>, SDL_Renderer* renderer);
	void render();
	~Map();
};

#endif
