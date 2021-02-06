#ifndef __MENU__
#define __MENU__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLHandler.h"

#define MAIN_CREATE 85
//#define MAIN_JOIN 110
#define MAIN_OPTIONS 110
#define MAIN_EXIT 135

#define OPT_RES 75
#define OPT_FS 100
#define OPT_BACK 125

enum MENU_TIPO {MAIN, OPTIONS, NEW, JOIN};
enum EVENT_KEY {UP, DOWN, RIGHT, LEFT, ENTER};

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
	int menu = MAIN;
	SDL_Window* menuWindow;
	SDL_Renderer* menuRenderer;

	SDL_Texture* createGame;
	//SDL_Texture* joinGame;
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

	SDLHandler mainMenu;
	SDLHandler optionsMenu;
	SDLHandler newGameMenu;
	//SDLHandler joinGameMenu;
	SDLHandler selection;

	void initialize();
	void createText();
    void renderMenu();
	void renderTextMain();
	void renderTextOptions();
	void pollEventMain(int key);
	void pollEventOptions(int key);
	void doActionMain();
	void doActionOpt();
public:
	Menu();
	bool getFullScreen();
	void render();
	void pollEvent();
	bool quitGame();
	bool enterGame();
    ~Menu();
};

#endif