#ifndef __MENU__
#define __MENU__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SpritesHandler.h"
#include "FilesHandler.h"
#include "TextHandler.h"
#include "../common_src/protectedQueue.h"
#include "../common_src/types.h"
#include "clientReceiver.h"
#include "clientTransmitter.h"
#include "SDL_Sounds.h"

#define LONG_SELECT 23
#define HIGH_SELECT 16

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

#define MAP_SELECT 75
#define MAP_PLAYERS 102
#define MAP_BOTS 129
#define MAP_BACK 156

#define JOIN_NAME 85
#define JOIN_MATCH 112
#define JOIN_PLAY 139
#define JOIN_BACK 166

enum VECTOR_MENUS { MENU_MAIN, MENU_OPTIONS, MENU_NEW, MENU_NEWNAME, MENU_NEWGAME,
	MENU_MAP, MENU_MAPSELECT, MENU_MAPPLAYER, MENU_MAPBOTS,
	MENU_JOIN, MENU_JOINNAME, MENU_JOINMATCH, MENU_LOBBY
};

enum SELECT_TIPO {ON_TEXT, OFF_TEXT, RES_ONE_TEXT, RES_TWO_TEXT,
	RES_THREE_TEXT
};

enum NUMBER_TEXT {TEXT_0, TEXT_1, TEXT_2, TEXT_3, TEXT_4};
enum EVENT_KEY {KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_ENTER};
enum TIPO_INPUT {CREATE_PLAYER, CREATE_GAME, JOIN_PLAYER};
enum ERROR_TIPO {ERROR_MAP, ERROR_MATCH, ERROR_NAME};

class Menu{
private:
	ClientReceiver &receiver;
	ClientTransmitter &transmitter;
    int &winLength;
	int &winHeight;
	SDL_Window* menuWindow;
	SDL_Renderer* menuRenderer;
	SDL_Sounds menuSounds;
	
    int longWin = 320;
    int highWin = 240;
	int longSelector = 23;
	int highSelector = 16;
	int highFont = 15;
	int zero = 0;
	int volMusic = 45;
	int volSFX = 20;

	int posSelectMain = MAIN_CREATE;
	int posSelectOpt = OPT_RES;
	int posSelectCreate = CREATE_NAME;
	int posSelectJoin = JOIN_NAME;
	int posSelectMap = MAP_SELECT;

	int offsetSelectMain = 27;
	int offsetSelectOpt = 35;
	int offsetSelectCreate = 27;
	int offsetSelectJoin = 27;
	int offsetSelectMap = 27;

	bool hasCreateGame = false;
	bool hasJoinGame = false;
	bool startGame = false;
	bool hasQuitGame = false;
	bool isFullScreen = false;

	bool validName = true;
	bool validMatch = true;

	bool nameChange = false;
	bool gameChange = false;
	bool joinChange = false;
	bool mapChange = false;
	bool numChange = false;
	
	int menu = MENU_MAIN;
	std::string nonString = " ";
	std::string namePlayer = "";
	std::string nameGame = "";
	std::string nameJoin = "";
	std::string mapName = "";
	int cantPlayers = 1;
	int cantBots = 0;

	std::vector<std::string> vectorSelectionText = {
		"On", "Off", "640x480", "800x600", "1024x768",
	};
	std::vector <std::string> vectorNumbers = {
		"0","1","2","3","4"
	};
	std::vector <std::string> vectorErrors = {
		"No maps loaded", "No matches found", 
		"Name already in use"
	};

	std::vector<std::string> vectorMatches;
	int matchPos = 0;

	std::vector<std::string> vectorMaps;
	int mapPos = 0;

	FilesHandler menuFiles;
	std::vector<std::string> vectorMenus;
	SpritesHandler menusHandler;
	SpritesHandler selection;

	TextHandler textSelectHandler;
	TextHandler textErrorHandler;
	TextHandler textNameHandler;
	TextHandler textGameCreateHandler;
	TextHandler textGameJoinHandler;
	TextHandler textMapHandler;
	TextHandler numPlayerHandler;
	TextHandler numBotsHandler;

	void initialize();
	void createText();
    void renderMenu();

	void renderTextOptions();
	void renderTextCreate();
	void renderTextJoin();
	void renderTextMap();

	void pollEventMain(const int &key);
	void pollEventOptions(const int &key);
	void pollEventCreate(const int &key);
	void pollEventMap(const int &key);
	void pollEventJoin(const int &key);

	void doActionMain();
	void doActionOpt();
	void doActionCreate();
	void doActionMap();
	void doActionJoin();

	bool validCreate();
	bool validJoin();

	bool inputText(std::string &input, int &x, int &y, const int &typeMenu);
	void renderCreateForInput(std::string &input, int &x, int &y, const int &typeMenu);
	
	void selectMatch();
	void renderSelectionMatch(int &pos);

	void selectMap();
	void renderSelectionMap(int &pos);

	void selectNumber(const int &typeMenu);
	void renderSelectionNumber(const int &typeMenu);

	void waitingInLobby();

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
	void setMatches(std::vector<std::string> &matches);
	void setMaps(std::vector<std::string> &maps);
	std::string playerName();
	std::string gameCreated();
	std::string gameJoined();
	bool joinedMatch();
    ~Menu();
};

#endif
