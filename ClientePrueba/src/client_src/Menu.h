#ifndef __MENU__
#define __MENU__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SpritesHandler.h"
#include "TextHandler.h"
#include "../common_src/protectedQueue.h"
#include "../common_src/types.h"
#include "clientReceiver.h"
#include "clientTransmitter.h"
#include "SDL_Sounds.h"

#define MAIN_CREATE 80
#define MAIN_JOIN 107
#define MAIN_OPTIONS 134
#define MAIN_EXIT 161

#define OPT_RES 74
#define OPT_FS 109
#define OPT_BACK 144

#define CREATE_NAME 69
#define CREATE_MATCH 96
#define CREATE_MAP 123
#define CREATE_PLAY 150
#define CREATE_BACK 177

#define JOIN_NAME 85
#define JOIN_MATCH 112
#define JOIN_PLAY 139
#define JOIN_BACK 166

enum VECTOR_MENUS { M_MAIN, M_OPTIONS, M_NEW, M_NEWNAME, M_NEWGAME,
 M_NEWMAP, M_JOIN, M_JOINNAME, M_JOINMATCH};

enum SELECT_TIPO {ON_TEXT, OFF_TEXT, RES_ONE_TEXT, RES_TWO_TEXT,
	RES_THREE_TEXT};
enum MENU_TIPO {MAIN_MENU, OPTIONS_MENU, CREATE_MENU, JOIN_MENU};
enum EVENT_KEY {KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_ENTER};
enum TIPO_INPUT {CREATE_PLAYER, CREATE_GAME, JOIN_PLAYER};
enum ERROR_TIPO {ERROR_MAP, ERROR_MATCH, ERROR_NAME};

class Menu{
private:
	ClientReceiver &receiver;
	ClientTransmitter &transmitter;
    int &winLargo;
	int &winAlto;
	SDL_Window* menuWindow;
	SDL_Renderer* menuRenderer;
	SDL_Sounds* menuSounds = SDL_Sounds::getInstance();
	
    int largo = 320;
    int alto = 240;

	int posSelectMain = MAIN_CREATE;
	int posSelectOpt = OPT_RES;
	int posSelectCreate = CREATE_NAME;
	int posSelectJoin = JOIN_NAME;

	int offsetSelectMain = 27;
	int offsetSelectOpt = 35;
	int offsetSelectCreate = 27;
	int offsetSelectJoin = 27;

	bool hasCreateGame = false;
	bool hasJoinGame = false;
	bool hasQuitGame = false;
	bool isFullScreen = false;

	bool validName = true;
	bool validMatch = true;

	bool nameChange = false;
	bool gameChange = false;
	bool joinChange = false;
	bool mapChange = true;
	
	int menu = MAIN_MENU;
	std::string namePlayer = "";
	std::string nameGame = "";
	std::string nameJoin = "";
	std::string mapName = "";

	std::vector<std::string> vectorSelectionText = {
		"On", "Off", "640x480", "800x600", "1024x768"
	};
	std::vector <std::string> vectorErrors = {
		"No maps loaded", "No matches found", 
		"Name already in use"
	};

	std::vector<std::string> vectorMatches;
	int matchPos = 0;

	std::vector<std::string> vectorMaps;
	int mapPos = 0;

	std::vector<std::string> vectorMenus = {
		"Media/Menu/MainMenu.png", "Media/Menu/OptionsMenu.png",
		"Media/Menu/NewMenu.png", "Media/Menu/NewMenuName.png",
		"Media/Menu/NewMenuGame.png", "Media/Menu/NewMenuMap.png",
		"Media/Menu/JoinMenu.png", "Media/Menu/JoinMenuName.png",
		"Media/Menu/JoinMenuGame.png"
	};
	SpritesHandler menusHandler;
	SpritesHandler selection;

	TextHandler textSelectHandler;
	TextHandler textErrorHandler;
	TextHandler textNameHandler;
	TextHandler textGameCreateHandler;
	TextHandler textGameJoinHandler;
	TextHandler textMapHandler;

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
	void selectMap();
	void renderSelectionMap(int pos);
public:
	Menu(ClientReceiver &r, 
		ClientTransmitter &t,
		int &l, 
		int &a);
	void render();
	void pollEvent();
	bool quitGame();
	bool createGame();
	bool joinGame();
	void setMatches(std::vector<std::string> matches);
	void setMaps(std::vector<std::string> maps);
	std::string playerName();
	std::string gameCreated();
	std::string gameJoined();
	bool joinedMatch();
    ~Menu();
};

#endif