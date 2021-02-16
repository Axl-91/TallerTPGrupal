#ifndef __MENU__
#define __MENU__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLHandler.h"
#include "Map.h"
#include "Settings.h"

#define MAIN_CREATE 85
#define MAIN_OPTIONS 110
#define MAIN_EXIT 135

#define OPT_RES 75
#define OPT_FS 100
#define OPT_BACK 125

enum MENU_TIPO {SPL,MAIN, OPTIONS, MAP};

class Menu{
private:
    int largo = 320;
    int alto = 240;
    int winLargo = 640;
	int winAlto = 480;
	int posSelectMain = MAIN_CREATE;
	int posSelectOpt = OPT_RES;
	bool hasEnterGame = false;
	bool hasQuitGame = false;
	bool isFullScreen = false;
	int menu = SPL;
	char* mapname =NULL;
	Map map;
	Settings sett;	

	SDL_Window* menuWindow;
	SDL_Renderer* menuRenderer;

	SDL_Texture* createGame;
	SDL_Texture* optionsGame;
	SDL_Texture* exitGame;
	SDL_Texture* resolution;
	SDL_Texture* fullScreen;
	SDL_Texture* on;
	SDL_Texture* off;
	SDL_Texture* resOne;
	SDL_Texture* resTwo;
	SDL_Texture* resThree;
	SDL_Texture* back;

	SDLHandler splash;
	SDLHandler mainMenu;
	SDLHandler optionsMenu;
	SDLHandler selection;
	SDLHandler main;	

	void initialize();
	void createText();
    void renderMenu();
	void renderTextMain();
	void renderTextOptions();
	void pollEventSplash(SDL_Event &event);
	void pollEventMain(SDL_Event &event);
	void pollEventOptions(SDL_Event &event);
	void pollEventMap(SDL_Event &event);
	void doActionMain();
	void doActionOpt();
public:
	Menu();
	bool getFullScreen();
	int getWinHeight() const;
	int getWinWidth() const;
	void render();
	void pollEvent();
	bool quitGame();
	bool enterGame();
    ~Menu();
};

#endif