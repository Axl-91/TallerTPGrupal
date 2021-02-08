#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Settings.h"
#include "Map.h"
#include "SDLHandler.h"

class Game{
private:	
	bool gameOver = false;
	bool isFullScreen = false;;
	int largo = 320;
    int alto = 240;
    int winLargo = 640;
	int winAlto = 480;
	Map map;
	SDLHandler main;	
	Settings sett;	
	SDL_Texture* textura;
	SDL_Window* window;
	SDL_Renderer* renderer;
	void exitPollEvent(SDL_Event &evento);
	void updatemodel();
	void initialize();
public:
	Game(bool isFullScreen,char * filename);
	void render();
	void update();
	bool isGameOver();
	~Game();
};

#endif