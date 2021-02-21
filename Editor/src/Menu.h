#ifndef __MENU__
#define __MENU__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLHandler.h"
#include "TextHandler.h"
#include "Map.h"
#include "Settings.h"

#define MAIN_CREATE 85
#define MAIN_EDIT 110
#define MAIN_OPTIONS 135
#define MAIN_EXIT 160

#define OPT_RES 75
#define OPT_FS 100
#define OPT_BACK 125

#define CRT_NAME 75
#define CRT_PLA 100
#define CRT_NEW 125

#define SAVE_S 75
#define SAVE_Q 140

#define EDT_MAP 75
#define EDT_IN 100

const int posVectorX = 180;
const int posVectorY = 80;

enum MENU_TIPO {SPL,MAIN,OPTIONS,MAP,CREATE,EDIT,SAV};

class Menu{
private:
    int lenght = 320;
    int high = 240;
    int winlenght = 640;
	int winhigh = 480;
	int mapPos = 0;

	int posSelectMain = MAIN_CREATE;
	int posSelectOpt = OPT_RES;
	int posSelectCrt = CRT_NAME;
	int posSelectSave = SAVE_S;
	int posSelectEdt = EDT_MAP;

	bool hasQuitGame = false;
	bool isFullScreen = false;
	int menu = SPL;
	bool nameChange = false;
	bool mapChange = true;

	std::vector<std::string> vectorMaps;	

	std::string mapname = "";	
	std::string mapelement = "";	

	SDL_Window* menuWindow;
	SDL_Renderer* menuRenderer;

	Settings sett;
	Map map;

	SDL_Texture* on;
	SDL_Texture* off;
	SDL_Texture* resOne;
	SDL_Texture* resTwo;
	SDL_Texture* resThree;	

	SDLHandler splash;
	SDLHandler mainMenu;
	SDLHandler mainCreate;
	SDLHandler mainEdit;
	SDLHandler optionsMenu;
	SDLHandler selection;
	SDLHandler main;
	SDLHandler save;	

	TextHandler textNameHandler;
	TextHandler textMapHandler;	

	SDL_Color white = {255, 255, 255};
	SDL_Color yellow = {255, 204, 0};

	void initialize();
	void createText();
    void renderMenu();
	void renderTextMain();
	void renderTextOptions();
	void renderTextCreate(bool);	
	void renderSelectionMap(int &pos);
	void renderTextEdit();

	void pollEventEdit(SDL_Event &event);
	void pollEventSplash(SDL_Event &event);
	void pollEventMain(SDL_Event &event);
	void pollEventOptions(SDL_Event &event);
	void pollEventMap(SDL_Event &event);
	void pollEventCreate(SDL_Event &event);
	void pollEventSave(SDL_Event &event);	

	void doActionMain();
	void doActionCreate();
	void doActionOpt();
	void doActionSave();
	void doActionEdit();	

	bool inputText(std::string &input, int x, int y);
	void renderCreateForInput(std::string &input, int x, int y);
	void selectMap();
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
