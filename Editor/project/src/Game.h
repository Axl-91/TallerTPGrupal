#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Settings.h"
#include "Arrow.h"
#include "Save.h"
#include "Textbox.h"
#include "Point.h"

class Game{
private:
    int largoReal = 320;
    int altoReal = 240;
	const char* title = "Game Editor";
	const char* imgFile = "background.png";
	bool gameOver = false;
	int winLargo;
	int winAlto;
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
public:
	Game(int largo, int ancho,char * filename);
	void render();
	void update();
	bool isGameOver();
	~Game();
};

#endif