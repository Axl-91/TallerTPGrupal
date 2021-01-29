#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Settings.h"
#include "Arrow.h"
#include "Textbox.h"
#include "Position.h"
#include "Map.h"

class Game{
private:
	const char* title = "Game Editor";
	const char* imgFile = "background.png";
	const char* font = "wolfenstein.ttf";
	TTF_Font *gFont = NULL;
	bool gameOver = false;
	int winLargo;
	int winAlto;
	Map map;
	Arrow arrow;
	Textbox maxplayers;	
	Textbox resW;
	Textbox resH;		
	Settings sett;	
	SDL_Texture* textura;
	SDL_Window* window;
	SDL_Renderer* renderer;
	void exitPollEvent(SDL_Event &evento);
    void getTexture();
    void fill();
    void initGui();
	void updatemodel();
public:
	Game(int largo, int ancho,char * filename);
	void render();
	void update();
	bool isGameOver();
	~Game();
};

#endif