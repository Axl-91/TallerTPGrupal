#include "Menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "SpritesHandler.h"

Menu::Menu(ClientReceiver &r, 
			ClientTransmitter &t, 
			int &l, 
			int &a): 
	// menuEventQ(eQ),
	receiver(r),
	transmitter(t),
	winLength(l),
	winHeight(a),
	menuFiles(fileMenus),
	vectorMenus(menuFiles.getVectorFiles()),
	menusHandler(vectorMenus, longWin, highWin),
	selection(fileSelector, 23, 33),
	textSelectHandler(vectorSelectionText),
	textErrorHandler(vectorErrors),
	textNameHandler(nonString),
	textGameCreateHandler(nonString),
	textGameJoinHandler(nonString),
	textMapHandler(nonString),
	numPlayerHandler(nonString),
	numBotsHandler(nonString)
{
		initialize();
		createText();
		menuSounds->playMusic(MENU_MUSIC, volMusic);
}

void Menu::createText(){
	SDL_Color yellow = {255, 204, 0};
	SDL_Color white = {255, 255, 255};
	textSelectHandler.setRenderer(menuRenderer, yellow);
	textErrorHandler.setRenderer(menuRenderer, yellow);
	textNameHandler.setRenderer(menuRenderer, white);
	textGameCreateHandler.setRenderer(menuRenderer, white);
	textGameJoinHandler.setRenderer(menuRenderer, white);
	textMapHandler.setRenderer(menuRenderer, white);
	numPlayerHandler.setRenderer(menuRenderer, white);
	numBotsHandler.setRenderer(menuRenderer, white);
}

void Menu::initialize(){
	int hayError;
    hayError = SDL_Init(SDL_INIT_VIDEO);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = SDL_CreateWindowAndRenderer(winLength, winHeight, 
		SDL_RENDERER_ACCELERATED, &menuWindow, &menuRenderer);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	SDL_SetWindowTitle(menuWindow, "WOLFENSTEIN 3D");
	SDL_RenderSetLogicalSize(menuRenderer, longWin, highWin);

	menusHandler.setRenderer(menuRenderer);
	selection.setRenderer(menuRenderer);

	TTF_Init();
}

void Menu::renderTextOptions(){
	int posX = 187;
	int posY = 73;
	int length = 45;

	if (winLength == 640){
		textSelectHandler.render(posX, posY, length, highFont, RES_ONE_TEXT);
	} else if (winLength == 800){
		textSelectHandler.render(posX, posY, length, highFont, RES_TWO_TEXT);
	} else if (winLength == 1024){
		textSelectHandler.render(posX, posY, length, highFont, RES_THREE_TEXT);
	}
	posY = 108;
	length = 15;
	if (isFullScreen){
		textSelectHandler.render(posX, posY, length, highFont, ON_TEXT);
	} else {
		textSelectHandler.render(posX, posY, length, highFont, OFF_TEXT);
	}
}

void Menu::renderTextCreate(){
	int posX, posY;
	if (nameChange){
		if (namePlayer.size() == 0){
			textNameHandler.setText(nonString);
		} else {
			textNameHandler.setText(namePlayer);
		}
		nameChange = false;
	}
	int sizeName = 7*namePlayer.size();
	posX = 168;
	posY = 69;
	textNameHandler.render(posX,posY,sizeName,highFont);


	if (gameChange && validMatch){
		if (nameGame.size() == 0){
			textGameCreateHandler.setText(nonString);
		} else {
			textGameCreateHandler.setText(nameGame);
		}
		gameChange = false;
	}
	posX = 163;
	posY = 96;
	if (!validMatch){
		int sizeError = 6*vectorErrors[ERROR_NAME].size();
		textErrorHandler.render(posX,posY,sizeError,highFont, ERROR_NAME);
	}else {
		int sizeGame = 7*nameGame.size();
		textGameCreateHandler.render(posX,posY,sizeGame,highFont);
	}
	if(vectorMaps.size() != 0){
		if (mapChange){
			textMapHandler.setText(vectorMaps[mapPos]);
			mapChange = false;
		}
		int mapNameSize = 7*vectorMaps[mapPos].size();
		posX = 170;
		posY = 123;
		textMapHandler.render(posX,posY,mapNameSize,highFont);
	} 
}

void Menu::renderTextMap(){
	int posX, posY;
	if (vectorMaps.size() != 0){
		if (mapChange){
			textMapHandler.setText(vectorMaps[mapPos]);
			mapChange = false;
		}
		int mapNameSize = 7*vectorMaps[mapPos].size();
		posX = 130;
		posY = 74;
		textMapHandler.render(posX,posY,mapNameSize,highFont);
	}
	if (numChange){
		numPlayerHandler.setText(vectorNumbers[cantPlayers]);
		numBotsHandler.setText(vectorNumbers[cantBots]);
	}
	int sizeNums = 7;
	posX = 161;
	posY = 102;
	numPlayerHandler.render(posX, posY, sizeNums, highFont);
	posX = 138;
	posY = 129;
	numBotsHandler.render(posX, posY, sizeNums, highFont);
}

void Menu::renderTextJoin(){
	int posX, posY;

	if (nameChange && validName){
		if (namePlayer.size() == 0){
			textNameHandler.setText(nonString);
		} else {
			textNameHandler.setText(namePlayer);
		}
		nameChange = false;
	}
	posX = 170;
	posY = 85;
	if (!validName){
		int sizeError = 6*vectorErrors[ERROR_NAME].size();
		textErrorHandler.render(posX, posY,sizeError,highFont,ERROR_NAME);
	} else {
		int sizeName = 7*namePlayer.size();
		textNameHandler.render(posX, posY,sizeName,highFont);
	}

	if (joinChange){
		if (nameJoin.size() == 0){
			textGameJoinHandler.setText(nonString);
		} else {
			textGameJoinHandler.setText(nameJoin);
		}
		joinChange = false;
	}

	int sizeJoin = 7*nameJoin.size();
	posX = 170;
	posY = 112;
	textGameJoinHandler.render(posX,posY,sizeJoin,highFont);
}

void Menu::renderMenu(){
	int posSelector;
    if (menu == MENU_MAIN){
		menusHandler.render(zero, zero, longWin, highWin, MENU_MAIN);
		posSelector = 60;
		selection.render(posSelector, posSelectMain, longSelector, highSelector);
	} else if (menu == MENU_OPTIONS){
		menusHandler.render(zero, zero ,longWin ,highWin, MENU_OPTIONS);
		posSelector = 60;
		selection.render(posSelector, posSelectOpt, longSelector, highSelector);
		renderTextOptions();
	} else if (menu == MENU_NEW){
		menusHandler.render(zero, zero ,longWin ,highWin, MENU_NEW);
		posSelector = 30;
		selection.render(posSelector, posSelectCreate, longSelector, highSelector);
		renderTextCreate();
	} else if (menu == MENU_MAP){
		menusHandler.render(zero, zero, longWin, highWin, MENU_MAP);
		posSelector = 60;
		selection.render(posSelector, posSelectMap, longSelector, highSelector);
		renderTextMap();
	} else if (menu == MENU_JOIN){
		menusHandler.render(zero, zero ,longWin ,highWin, MENU_JOIN);
		posSelector = 36;
		selection.render(posSelector, posSelectJoin, longSelector, highSelector);
		renderTextJoin();
	} else if (menu == MENU_LOBBY){
		menusHandler.render(zero, zero, longWin, highWin, MENU_LOBBY);
		waitingInLobby();
	}
}

void Menu::render(){
	renderMenu();
    SDL_RenderPresent(menuRenderer);
}

void Menu::doActionMain(){
	switch (posSelectMain){
		case MAIN_CREATE:
			menu = MENU_NEW;
			posSelectCreate = CREATE_NAME;
			break;
		case MAIN_JOIN:
			menu = MENU_JOIN;
			posSelectJoin = JOIN_NAME;
			break;
		case MAIN_OPTIONS:
			menu = MENU_OPTIONS;
			posSelectOpt = OPT_RES;
			break;
		case MAIN_EXIT:
			hasQuitGame = true;
			break;
	}
}

void Menu::doActionOpt(){
	switch (posSelectOpt){
		case OPT_RES:
			if (winLength == 640){
				winLength = 800;
				winHeight = 600;
			} else if (winLength == 800){
				winLength = 1024;
				winHeight = 768;
			} else if (winLength == 1024){
				winLength = 640;
				winHeight = 480;
			}
			SDL_SetWindowSize(menuWindow, winLength, winHeight);
			SDL_SetWindowPosition(menuWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			break;
		case OPT_FS:
			if (!isFullScreen){
				SDL_SetWindowFullscreen(menuWindow, SDL_WINDOW_FULLSCREEN);
				isFullScreen = true;
			} else {
				SDL_SetWindowFullscreen(menuWindow, 0);
				SDL_SetWindowSize(menuWindow, winLength, winHeight);
				SDL_SetWindowPosition(menuWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				isFullScreen = false;
			}
			break;
		case OPT_BACK:
			menu = MENU_MAIN;
			break;
	}
}

// Imprime el texto que se va ingresando en las opciones
void Menu::renderCreateForInput(std::string &input, int &x, int &y, const int &typeMenu){
	SDL_Color yellow = {255, 204, 0};
	SDL_RenderClear(menuRenderer);
	if (typeMenu == CREATE_PLAYER){
		menusHandler.render(zero, zero ,longWin ,highWin, MENU_NEWNAME);
	} else if (typeMenu == CREATE_GAME){
		menusHandler.render(zero, zero ,longWin ,highWin, MENU_NEWGAME);
	}else if (typeMenu == JOIN_PLAYER){
		menusHandler.render(zero, zero, longWin, highWin, MENU_JOINNAME);
	}
	if (input.size() > 0){
		TextHandler handler(input);
		handler.setRenderer(menuRenderer, yellow);
		int sizeName = 7*input.size();
		handler.render(x,y,sizeName,highFont);
	}
	SDL_RenderPresent(menuRenderer);
}

bool Menu::inputText(std::string &input, int &x, int &y, const int &typeMenu){
	bool hasChange = false;
	renderCreateForInput(input, x, y, typeMenu);
	bool salida = false;
	SDL_StartTextInput();
	SDL_Event event;
	while (!salida){
		bool renderText = false;
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_TEXTINPUT && input.size() < 15){
				input += event.text.text;
				renderText = true;
			}
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
					case SDLK_RETURN:
						salida = true;
						hasChange = true;
						break;
					case SDLK_ESCAPE:
						salida = true;
						break;
					case SDLK_BACKSPACE:
						if (input.size() > 0){
							input.pop_back();
							renderText = true;
						}
						break;
				}
			}
		}
		if (renderText){
			renderCreateForInput(input, x, y, typeMenu);
		}
	}
	SDL_StopTextInput();
	return hasChange;
}

// Imprime los mapas
void Menu::renderSelectionMap(int &pos){
	SDL_Color yellow = {245,244,0};
	SDL_RenderClear(menuRenderer);
	menusHandler.render(zero, zero, longWin, highWin, MENU_MAPSELECT);
	int posX = 130;
	int posY = 74;

	if (vectorMaps.size() > 0){
		TextHandler handler(vectorMaps[pos]);
		handler.setRenderer(menuRenderer, yellow);
		int sizeJoin = 7*vectorMaps[pos].size();
		handler.render(posX,posY,sizeJoin,highFont);
	} else {
		int sizeJoin = 6*vectorErrors[ERROR_MAP].size();
		textErrorHandler.render(posX,posY,sizeJoin,highFont, ERROR_MAP);
	}
	SDL_RenderPresent(menuRenderer);
}

void setMatchVector(std::vector<std::string> &vectorMatches, std::string list){
	std::stringstream aStream(list);
	std::cout << "estoy por imprimir listado de maps" << list <<std::endl;
	std::string aux;
	
	vectorMatches.clear();
	while (getline(aStream,aux)){
        if (aux.length() == 0)
            continue;
		vectorMatches.push_back(aux);
	}
}

void Menu::selectMap(){
	bool selected = false;

	std::string auxString;
	receiver.receiveString(auxString);

	if(auxString.length() > 0)
		setMatchVector(vectorMaps, auxString);

	SDL_Event event;
	renderSelectionMap(mapPos);

	while (!selected){
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
					case SDLK_RIGHT:
						if (vectorMaps.size() > mapPos+1){
							mapPos += 1;
							renderSelectionMap(mapPos);
						}
						break;
					case SDLK_LEFT:
						if (mapPos > 0){
							mapPos -= 1;
							renderSelectionMap(mapPos);
						}
						break;
					case SDLK_RETURN:
						if (vectorMaps.size() > 0){
							mapName = vectorMaps[mapPos];
							mapChange = true;
							selected = true;
						}
						break;
					case SDLK_ESCAPE:
						selected = true;
						break;
				}
			}
		}
	}
}

bool Menu::validCreate(){
	bool hasName = namePlayer.size() > 0;
	bool hasGame = nameGame.size() > 0;
	bool hasMap = mapName.size() > 0;

	return (hasName && hasGame && hasMap && validMatch);
}

void Menu::doActionCreate(){
	menu_event_t event;
	int posX, posY;
	switch (posSelectCreate){
		case CREATE_NAME:
			posX = 168;
			posY = 69;
			nameChange = inputText(namePlayer,posX,posY, CREATE_PLAYER);
			event.event = NEW_NAME;
			event.info = namePlayer;
			transmitter.sendMenuEvent(event);
			// menuEventQ.push(event);
			break;
		case CREATE_MATCH:
			posX = 163;
			posY = 96;
			gameChange = inputText(nameGame,posX,posY, CREATE_GAME);

			/*REVISAR SI EL NOMBRE DE LA PARTIDA YA EXISTE
			Y MODIFICAR LA VARIABLE VALIDMATCH */

			break;
		case CREATE_MAP:
			posSelectMap = MAP_SELECT;
			menu = MENU_MAP;
			break;
		case CREATE_PLAY:
			if (validCreate()){
				event.event = NEW_MATCH;
				event.info = nameGame;
				transmitter.sendMenuEvent(event);
				hasCreateGame = true;
				//menu = MENU_LOBBY;
			}
			break;
		case CREATE_BACK:
			menu = MENU_MAIN;
			break;
	}
}

void Menu::renderSelectionNumber(const int &typeMenu){
	SDL_Color yellow = {255, 204, 0};
	int posX, posY, number;
	SDL_RenderClear(menuRenderer);

	if (typeMenu == MAP_PLAYERS){
		posX = 161;
		posY = 102;
		number = cantPlayers;
		menusHandler.render(zero, zero, longWin, highWin, MENU_MAPPLAYER);
	} else {
		posX = 138;
		posY = 129;
		number = cantBots;
		menusHandler.render(zero, zero, longWin, highWin, MENU_MAPBOTS);
	}

	TextHandler handler(vectorNumbers[number]);
	handler.setRenderer(menuRenderer, yellow);
	int sizeName = 7;
	handler.render(posX,posY,sizeName,highFont);

	SDL_RenderPresent(menuRenderer);
}

void Menu::selectNumber(const int &typeMenu){
	bool selected = false;
	SDL_Event event;
	renderSelectionNumber(typeMenu);

	while (!selected){
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
					case SDLK_LEFT:
						if (typeMenu == MAP_PLAYERS){
							if (cantPlayers > 1){
								cantPlayers --;
							}
						} else {
							if (typeMenu == MAP_BOTS){
								if (cantBots > 0){
									cantBots --;
								}
							}
						}
						renderSelectionNumber(typeMenu);
						break;
					case SDLK_RIGHT:
						if (typeMenu == MAP_PLAYERS){
							if (cantPlayers < 4){
								cantPlayers ++;
							}
						} else {
							if (typeMenu == MAP_BOTS){
								if (cantBots < 4){
									cantBots ++;
									std::cout << "estoy aca" << std::endl;
								}
							}
						}
						renderSelectionNumber(typeMenu);
						break;
					case SDLK_RETURN:
						numChange = true;
						selected = true;
						break;
					case SDLK_ESCAPE:
						selected = true;
						break;
				}
			}
		}
	}
}

void Menu::doActionMap(){
	menu_event_t event;
	switch (posSelectMap){
		case MAP_SELECT:
			event.event = GET_MAPS;
			event.info = "";
			transmitter.sendMenuEvent(event);
			selectMap();
			event.event = SET_MAP;
			event.info = mapName;
			transmitter.sendMenuEvent(event);
			break;
		case MAP_PLAYERS:
			event.event = SELECT_MAX_PLAYER;
			event.info = "";
			selectNumber(MAP_PLAYERS);
			event.info += std::to_string(cantPlayers);
			transmitter.sendMenuEvent(event);
			break;
		case MAP_BOTS:
			event.event = SELECT_NUMBER_OF_BOTS;
			event.info = "";
			selectNumber(MAP_BOTS);
			event.info += std::to_string(cantBots);
			transmitter.sendMenuEvent(event);
			break;
		case MAP_BACK:
			menu = MENU_NEW;
			break;
	}
}

// Imprime las partidas
void Menu::renderSelectionMatch(int &pos){
	SDL_Color yellow = {245,244,0};
	SDL_RenderClear(menuRenderer);
	menusHandler.render(zero, zero, longWin, highWin, MENU_JOINMATCH);

	int posX = 170;
	int posY = 112;

	if (vectorMatches.size() > 0){
		TextHandler handler(vectorMatches[pos]);
		handler.setRenderer(menuRenderer, yellow);
		int sizeJoin = 7*vectorMatches[pos].size();
		handler.render(posX,posY,sizeJoin,highFont);
	} else {
		int sizeJoin = 5*vectorErrors[ERROR_MATCH].size();
		textErrorHandler.render(posX,posY,sizeJoin,highFont, ERROR_MATCH);
	}
	SDL_RenderPresent(menuRenderer);
}

void Menu::selectMatch(){

	bool selected = false;

	std::string auxString;
	receiver.receiveString(auxString);

	if(auxString.length() > 0)
		setMatchVector(vectorMatches, auxString);
	SDL_Event event;

	renderSelectionMatch(matchPos);

	while (!selected){
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
					case SDLK_RIGHT:
						if (vectorMatches.size() > matchPos+1){
							matchPos += 1;
							renderSelectionMatch(matchPos);
						}
						break;
					case SDLK_LEFT:
						if (matchPos > 0){
							matchPos -= 1;
							renderSelectionMatch(matchPos);
						}
						break;
					case SDLK_RETURN:
						if (vectorMatches.size() > 0){
							nameJoin = vectorMatches[matchPos];
							selected = true;
							joinChange = true;
						}
						break;
					case SDLK_ESCAPE:
						selected = true;
						break;
				}
			}
		}
	}
}

bool Menu::validJoin(){
	bool hasName = namePlayer.size() > 0;
	bool hasGame = nameJoin.size() > 0;

	return (hasName && hasGame && validName);
}

void Menu::doActionJoin(){
	menu_event_t event;
	int posX, posY;
	switch (posSelectJoin){
		case JOIN_NAME:
			posX = 170;
			posY = 85;
			nameChange = inputText(namePlayer,posX,posY, JOIN_PLAYER);
			if (nameGame.size() > 0){

				/*LUEGO DE INGRESAR EL NOMBRE REVISAR SI EXISTE
				EN LA PARTIDA Y MODIFICAR EL VALIDNAME*/

			}
			break;
		case JOIN_MATCH:
			event.event = GET_MATCHES;
			event.info = "";
			transmitter.sendMenuEvent(event);
			// menuEventQ.push(event);
			selectMatch();

			/*LUEGO DE SELECCIONAR PARTIDA REVISAR SI EXISTE EL NOMBRE
			EN LA PARTIDA Y MODIFICAR EL VALIDNAME*/

			break;
		case JOIN_PLAY:
			if (validJoin()){
				event.event = JOIN;
				event.info = nameJoin;
				transmitter.sendMenuEvent(event);
				// menuEventQ.push(event);
				hasJoinGame = true;
				//menu = MENU_LOBBY;
			}
			break;
		case JOIN_BACK:
			menu = MENU_MAIN;
			break;
	}
}

void Menu::pollEventMain(const int &key){
	switch(key){
		case KEY_DOWN:
			if (posSelectMain != MAIN_EXIT){
				posSelectMain += offsetSelectMain;
			} else {
				posSelectMain = MAIN_CREATE;
			}
			break;
		case KEY_UP:
			if(posSelectMain != MAIN_CREATE){
				posSelectMain -= offsetSelectMain;
			} else {
				posSelectMain = MAIN_EXIT;
			}
			break;
		case KEY_ENTER:
			doActionMain();
			break;
	}
}

void Menu::pollEventOptions(const int &key){
	switch(key){
		case KEY_DOWN:
			if (posSelectOpt != OPT_BACK){
				posSelectOpt += offsetSelectOpt;
			} else {
				posSelectOpt = OPT_RES;
			}
			break;
		case KEY_UP:
			if(posSelectOpt != OPT_RES){
				posSelectOpt -= offsetSelectOpt;
			} else {
				posSelectOpt = OPT_BACK;
			}
			break;
		case KEY_ENTER:
			doActionOpt();
			break;
	}
}

void Menu::pollEventCreate(const int &key){
	switch(key){
		case KEY_DOWN:
			if (posSelectCreate != CREATE_BACK){
				posSelectCreate += offsetSelectCreate;
			} else {
				posSelectCreate = CREATE_NAME;
			}
			break;
		case KEY_UP:
			if(posSelectCreate != CREATE_NAME){
				posSelectCreate -= offsetSelectCreate;
			} else {
				posSelectCreate = CREATE_BACK;
			}
			break;
		case KEY_ENTER:
			doActionCreate();
			break;
	}
}

void Menu::pollEventMap(const int &key){
	switch(key){
		case KEY_DOWN:
			if (posSelectMap != MAP_BACK){
				posSelectMap += offsetSelectMap;
			} else {
				posSelectMap = MAP_SELECT;
			}
			break;
		case KEY_UP:
			if(posSelectMap != MAP_SELECT){
				posSelectMap -= offsetSelectMap;
			} else {
				posSelectMap = MAP_BACK;
			}
			break;
		case KEY_ENTER:
			doActionMap();
			break;
	}
}

void Menu::pollEventJoin(const int &key){
	switch(key){
		case KEY_DOWN:
			if (posSelectJoin != JOIN_BACK){
				posSelectJoin += offsetSelectJoin;
			} else {
				posSelectJoin = JOIN_NAME;
			}
			break;
		case KEY_UP:
			if(posSelectJoin != JOIN_NAME){
				posSelectJoin -= offsetSelectJoin;
			} else {
				posSelectJoin = JOIN_BACK;
			}
			break;
		case KEY_ENTER:
			doActionJoin();
			break;
	}
}

void Menu::pollEvent(){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
		    hasQuitGame = true;
	    }
	    if (event.type == SDL_KEYDOWN){
		    switch(event.key.keysym.sym){
		    	case SDLK_ESCAPE:
		    		if (menu == MENU_MAP){
						menu = MENU_NEW;
					} else {
						menu = MENU_MAIN;
					}
					break;
				case SDLK_DOWN:
					menuSounds->playEffect(MENU_MOVE, volSFX);
					switch (menu){
						case MENU_MAIN:
							pollEventMain(KEY_DOWN);
							break;
						case MENU_OPTIONS:
							pollEventOptions(KEY_DOWN);
							break;
						case MENU_NEW:
							pollEventCreate(KEY_DOWN);
							break;
						case MENU_MAP:
							pollEventMap(KEY_DOWN);
							break;
						case MENU_JOIN:
							pollEventJoin(KEY_DOWN);
							break;
					}
					break;
				case SDLK_UP:
					menuSounds->playEffect(MENU_MOVE, volSFX);
					switch (menu){
						case MENU_MAIN:
							pollEventMain(KEY_UP);
							break;
						case MENU_OPTIONS:
							pollEventOptions(KEY_UP);
							break;
						case MENU_NEW:
							pollEventCreate(KEY_UP);
							break;
						case MENU_MAP:
							pollEventMap(KEY_UP);
							break;
						case MENU_JOIN:
							pollEventJoin(KEY_UP);
							break;
					}
					break;
				case SDLK_RETURN:
					menuSounds->playEffect(MENU_SELECT,volSFX);
					switch (menu){
						case MENU_MAIN:
							pollEventMain(KEY_ENTER);
							break;
						case MENU_OPTIONS:
							pollEventOptions(KEY_ENTER);
							break;
						case MENU_NEW:
							pollEventCreate(KEY_ENTER);
							break;
						case MENU_MAP:
							pollEventMap(KEY_ENTER);
							break;
						case MENU_JOIN:
							pollEventJoin(KEY_ENTER);
							break;
					}
					break;
		    }
		}
    }
}

void Menu::waitingInLobby(){
	/* Imprimo los numeros de jugadores que hay y que tienen que
	haber para que empieze la partida y luego reviso si estan todos
	y en caso positivo seteo startGame en true */
}

bool Menu::quitGame(){
	if (hasCreateGame){
		SDL_HideWindow(menuWindow);
	}
    return hasQuitGame;
}

bool Menu::createGame(){
	if (hasCreateGame){
		SDL_HideWindow(menuWindow);
	}
	return hasCreateGame;
}

bool Menu::joinGame(){
	if (hasCreateGame){
		SDL_HideWindow(menuWindow);
	}
	return hasJoinGame;
}

void Menu::setMatches(std::vector<std::string> &matches){
	vectorMatches = matches;
}

void Menu::setMaps(std::vector<std::string> &maps){
	vectorMaps = maps;
}

std::string Menu::playerName(){
	return namePlayer;
}

std::string Menu::gameCreated(){
	return nameGame;
}

std::string Menu::gameJoined(){
	return nameJoin;
}

Menu::~Menu(){
	if (menuRenderer){
		SDL_DestroyRenderer(menuRenderer);
		menuRenderer = nullptr;
	}
	if (menuWindow){
		SDL_DestroyWindow(menuWindow);
		menuWindow = nullptr;
	}
	TTF_Quit();
	SDL_Quit();
	menuSounds->close();
}
bool Menu::joinedMatch(){
	return hasJoinGame | hasCreateGame;
}
