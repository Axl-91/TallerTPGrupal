#ifndef __MENU__
#define __MENU__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SDLHandler.h"
#include "TextHandler.h"
#include "../common_src/protectedQueue.h"
#include "../common_src/types.h"
#include "clientReceiver.h"

#define MAIN_CREATE 80
#define MAIN_JOIN 107
#define MAIN_OPTIONS 134
#define MAIN_EXIT 161

#define OPT_RES 74
#define OPT_FS 109
#define OPT_BACK 144

#define CREATE_NAME 74
#define CREATE_MATCH 109
#define CREATE_PLAY 144
#define CREATE_BACK 179

#define JOIN_NAME 85
#define JOIN_MATCH 112
#define JOIN_PLAY 139
#define JOIN_BACK 166

enum SELECT_TIPO {ON_TEXT, OFF_TEXT, RES_ONE_TEXT, RES_TWO_TEXT,
	RES_THREE_TEXT};
enum MENU_TIPO {MAIN_MENU, OPTIONS_MENU, CREATE_MENU, JOIN_MENU};
enum EVENT_KEY {UP, DOWN, RIGHT, LEFT, ENTER};
enum TIPO_INPUT {CREATE_PLAYER, CREATE_GAME, JOIN_PLAYER};

class Menu{
private:
	ProtectedQueue<menu_event_t> &menuEventQ;
	ClientReceiver &receiver;
	SDL_Window* menuWindow;
	SDL_Renderer* menuRenderer;
	
    int largo = 320;
    int alto = 240;
    int winLargo = 640;
	int winAlto = 480;

	int posSelectMain = MAIN_CREATE;
	int posSelectOpt = OPT_RES;
	int posSelectCreate = CREATE_NAME;
	int posSelectJoin = JOIN_NAME;

	int offsetSelectMain = 27;
	int offsetSelectOpt = 35;
	int offsetSelectCreate = 35;
	int offsetSelectJoin = 27;

	bool hasCreateGame = false;
	bool hasJoinGame = false;
	bool hasQuitGame = false;
	bool isFullScreen = false;
	bool nameChange = false;
	bool gameChange = false;
	bool joinChange = false;
	int menu = MAIN_MENU;
	std::string namePlayer = "";
	std::string nameGame = "";
	std::string nameJoin = "";

	std::vector<std::string> vectorSelectionText = {
		"On", "Off", "640x480", "800x600", "1024x768"
	};

	std::vector<std::string> vectorMatches;
	// std::vector<std::string> vectorMatches = { "pichiwar" };
	int matchPos = 0;

	/*Crear o modificar SDLHandler en el que pueda
	 meter muchas imagenes juntas */
	SDLHandler mainMenu;
	SDLHandler optionsMenu;
	SDLHandler newGameMenu;
	SDLHandler newGameTextPlayer;
	SDLHandler newGameTextGame;
	SDLHandler joinGameMenu;
	SDLHandler joinGameTextPlayer;
	SDLHandler joinGameTextGame;
	SDLHandler selection;

	TextHandler textSelectHandler;
	TextHandler textNameHandler;
	TextHandler textGameCreateHandler;
	TextHandler textGameJoinHandler;

	void initialize();
	void createText();
    void renderMenu();
	void renderTextOptions();
	void renderTextCreate();
	void renderTextJoin();
	void pollEventMain(int key);
	void pollEventOptions(int key);
	void pollEventCreate(int key);
	void pollEventJoin(int key);
	void doActionMain();
	void doActionOpt();
	void doActionCreate();
	void doActionJoin();
	bool inputText(std::string &input, int x, int y, int tipo);
	void renderCreateForInput(std::string &input, int x, int y, int tipo);
	void selectMatch();
	void renderSelectionMatch(int pos);
public:
	Menu(ProtectedQueue<menu_event_t> &eQ, ClientReceiver &r);
	void render();
	void pollEvent();
	bool quitGame();
	bool createGame();
	bool joinGame();
	void setMatches(std::vector<std::string> matches);
	std::string playerName();
	std::string gameCreated();
	std::string gameJoined();
    ~Menu();
};

#endif