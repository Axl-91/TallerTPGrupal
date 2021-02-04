#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Menu.h"
#include "SDLHandler.h"

Menu::Menu(): 
	mainMenu(0, 0, largo, alto, "Media/Menu/MainMenu.png"),
	optionsMenu(0, 0, largo, alto, "Media/Menu/OptionsMenu.png"),
	newGameMenu(0, 0, largo, alto, "Media/Menu/NewMenu.png"),
	newGameTextPlayer(0, 0, largo, alto, "Media/Menu/NewMenuName.png"),
	newGameTextGame(0, 0, largo, alto, "Media/Menu/NewMenuGame.png"),
	joinGameMenu(0, 0, largo, alto, "Media/Menu/JoinMenu.png"),
	joinGameTextPlayer(0, 0, largo, alto, "Media/Menu/JoinMenuName.png"),
	joinGameTextGame(0, 0, largo, alto, "Media/Menu/JoinMenuGame.png"),
	selection(0, 0, 23, 33, "Media/Menu/SelectionMenu.png"),
	textSelectHandler(vectorSelectionText),
	textNameHandler(" "),
	textGameCreateHandler(" "),
	textGameJoinHandler(" ")
{
		initialize();
		createText();
}

void Menu::createText(){
	SDL_Color yellow = {255, 204, 0};
	SDL_Color white = {255, 255, 255};
	textSelectHandler.setRenderer(menuRenderer, yellow);
	textNameHandler.setRenderer(menuRenderer, white);
	textGameCreateHandler.setRenderer(menuRenderer, white);
	textGameJoinHandler.setRenderer(menuRenderer, white);
}

void Menu::initialize(){
	int hayError;
    hayError = SDL_Init(SDL_INIT_VIDEO);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = SDL_CreateWindowAndRenderer(winLargo, winAlto, 
		SDL_RENDERER_ACCELERATED, &menuWindow, &menuRenderer);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	SDL_SetWindowTitle(menuWindow, "WOLFENSTEIN 3D");
	SDL_RenderSetLogicalSize(menuRenderer, largo, alto);

	mainMenu.setRenderer(menuRenderer);
	optionsMenu.setRenderer(menuRenderer);
	newGameMenu.setRenderer(menuRenderer);
	newGameTextPlayer.setRenderer(menuRenderer);
	newGameTextGame.setRenderer(menuRenderer);
	joinGameMenu.setRenderer(menuRenderer);
	joinGameTextPlayer.setRenderer(menuRenderer);
	joinGameTextGame.setRenderer(menuRenderer);
	selection.setRenderer(menuRenderer);

	TTF_Init();
}

void Menu::renderTextOptions(){

	if (winLargo == 640){
		textSelectHandler.render(187, 73, 45, 15, RES_ONE_TEXT);
	} else if (winLargo == 800){
		textSelectHandler.render(187, 73, 45, 15, RES_TWO_TEXT);
	} else if (winLargo == 1024){
		textSelectHandler.render(187, 73, 45, 15, RES_THREE_TEXT);
	}
	
	if (isFullScreen){
		textSelectHandler.render(187, 108, 15, 15, ON_TEXT);
	} else {
		textSelectHandler.render(187, 108, 15, 15, OFF_TEXT);
	}
}

void Menu::renderTextCreate(){
	if (nameChange){
		if (namePlayer.size() == 0){
			textNameHandler.setText(" ");
		} else {
			textNameHandler.setText(namePlayer);
		}
		nameChange = false;
	}
	int sizeName = 7*namePlayer.size();
	textNameHandler.render(168,73,sizeName,15);

	if (gameChange){
		if (nameGame.size() == 0){
			textGameCreateHandler.setText(" ");
		} else {
			textGameCreateHandler.setText(nameGame);
		}
		gameChange = false;
	}

	int sizeGame = 7*nameGame.size();
	textGameCreateHandler.render(163,108,sizeGame,15);
}

void Menu::renderTextJoin(){
	if (nameChange){
		if (namePlayer.size() == 0){
			textNameHandler.setText(" ");
		} else {
			textNameHandler.setText(namePlayer);
		}
		nameChange = false;
	}
	int sizeName = 7*namePlayer.size();
	textNameHandler.render(170,85,sizeName,15);

	if (joinChange){
		if (nameJoin.size() == 0){
			textGameJoinHandler.setText(" ");
		} else {
			textGameJoinHandler.setText(nameJoin);
		}
		joinChange = false;
	}

	int sizeJoin = 7*nameJoin.size();
	textGameJoinHandler.render(170,112,sizeJoin,15);
}

void Menu::renderMenu(){
    if (menu == MAIN_MENU){
		mainMenu.render(0, 0, largo, alto);
		selection.render(60, posSelectMain, 23, 16);
	} else if (menu == OPTIONS_MENU){
		optionsMenu.render(0, 0 ,largo ,alto);
		selection.render(60, posSelectOpt, 23, 16);
		renderTextOptions();
	} else if (menu == CREATE_MENU){
		newGameMenu.render(0, 0 ,largo ,alto);
		selection.render(30, posSelectCreate, 23, 16);
		renderTextCreate();
	} else if (menu == JOIN_MENU){
		joinGameMenu.render(0, 0 ,largo ,alto);
		selection.render(36, posSelectJoin, 23, 16);
		renderTextJoin();
	}
}

void Menu::render(){
	renderMenu();
    SDL_RenderPresent(menuRenderer);
}

void Menu::doActionMain(){
	switch (posSelectMain){
		case MAIN_CREATE:
			menu = CREATE_MENU;
			posSelectCreate = CREATE_NAME;
			break;
		case MAIN_JOIN:
			menu = JOIN_MENU;
			break;
		case MAIN_OPTIONS:
			menu = OPTIONS_MENU;
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
			if (winLargo == 640){
				winLargo = 800;
				winAlto = 600;
			} else if (winLargo == 800){
				winLargo = 1024;
				winAlto = 768;
			} else if (winLargo == 1024){
				winLargo = 640;
				winAlto = 480;
			}
			SDL_SetWindowSize(menuWindow, winLargo, winAlto);
			SDL_SetWindowPosition(menuWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			break;
		case OPT_FS:
			if (!isFullScreen){
				SDL_SetWindowFullscreen(menuWindow, SDL_WINDOW_FULLSCREEN);
				isFullScreen = true;
			} else {
				SDL_SetWindowFullscreen(menuWindow, 0);
				SDL_SetWindowSize(menuWindow, winLargo, winAlto);
				SDL_SetWindowPosition(menuWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				isFullScreen = false;
			}
			break;
		case OPT_BACK:
			menu = MAIN_MENU;
			break;
	}
}

void Menu::renderCreateForInput(std::string &input, int x, int y, int tipo){
	SDL_Color yellow = {255, 204, 0};
	SDL_RenderClear(menuRenderer);
	if (tipo == CREATE_PLAYER){
		newGameTextPlayer.render(0, 0 ,largo ,alto);
	} else if (tipo == CREATE_GAME){
		newGameTextGame.render(0, 0 ,largo ,alto);
	}else if (tipo == JOIN_PLAYER){
		joinGameTextPlayer.render(0, 0, largo, alto);
	}
	if (input.size() > 0){
		TextHandler handler(input);
		handler.setRenderer(menuRenderer, yellow);
		int sizeName = 7*input.size();
		handler.render(x,y,sizeName,15);
	}
	SDL_RenderPresent(menuRenderer);
}

bool Menu::inputText(std::string &input, int x, int y, int tipo){
	bool hasChange = false;
	renderCreateForInput(input, x, y, tipo);
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
			renderCreateForInput(input, x, y, tipo);
		}
	}
	SDL_StopTextInput();
	return hasChange;
}

void Menu::doActionCreate(){
	switch (posSelectCreate){
		case CREATE_NAME:
			nameChange = inputText(namePlayer,168,73, CREATE_PLAYER);
			break;
		case CREATE_MATCH:
			gameChange = inputText(nameGame,163,108, CREATE_GAME);
			break;
		case CREATE_PLAY:
			if (namePlayer.size() > 0 && nameGame.size() > 0){
				hasCreateGame = true;
			}
			break;
		case CREATE_BACK:
			menu = MAIN_MENU;
			break;
	}
}

void Menu::renderSelectionMatch(int pos){
	SDL_Color yellow = {245,244,0};
	SDL_RenderClear(menuRenderer);
	joinGameTextGame.render(0, 0, largo, alto);
	if (vectorMatches.size() > 0){
		TextHandler handler(vectorMatches[pos]);
		handler.setRenderer(menuRenderer, yellow);
		int sizeJoin = 7*vectorMatches[pos].size();
		handler.render(170,112,sizeJoin,15);
	} else {
		std::string msj = "No Matches";
		TextHandler handler(msj);
		handler.setRenderer(menuRenderer, yellow);
		int sizeJoin = 7*msj.size();
		handler.render(170,112,sizeJoin,15);
	}
	SDL_RenderPresent(menuRenderer);
}

void Menu::selectMatch(){
	bool selected = false;
	renderSelectionMatch(matchPos);
	SDL_Event event;

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

void Menu::doActionJoin(){
	switch (posSelectJoin){
		case JOIN_NAME:
			nameChange = inputText(namePlayer,170,85, JOIN_PLAYER);
			break;
		case JOIN_MATCH:
			selectMatch();
			break;
		case JOIN_PLAY:
			if (namePlayer.size() > 0 && nameJoin.size() > 0){
				hasJoinGame = true;
			}
			break;
		case JOIN_BACK:
			menu = MAIN_MENU;
			break;
	}
}

void Menu::pollEventMain(int key){
	switch(key){
		case DOWN:
			if (posSelectMain != MAIN_EXIT){
				posSelectMain += offsetSelectMain;
			} else {
						posSelectMain = MAIN_CREATE;
			}
			break;
		case UP:
			if(posSelectMain != MAIN_CREATE){
				posSelectMain -= offsetSelectMain;
			} else {
				posSelectMain = MAIN_EXIT;
			}
			break;
		case ENTER:
			doActionMain();
			break;
	}
}

void Menu::pollEventOptions(int key){
	switch(key){
		case DOWN:
			if (posSelectOpt != OPT_BACK){
				posSelectOpt += offsetSelectOpt;
			} else {
						posSelectOpt = OPT_RES;
			}
			break;
		case UP:
			if(posSelectOpt != OPT_RES){
				posSelectOpt -= offsetSelectOpt;
			} else {
				posSelectOpt = OPT_BACK;
			}
			break;
		case ENTER:
			doActionOpt();
			break;
	}
}

void Menu::pollEventCreate(int key){
	switch(key){
		case DOWN:
			if (posSelectCreate != CREATE_BACK){
				posSelectCreate += offsetSelectCreate;
			} else {
						posSelectCreate = CREATE_NAME;
			}
			break;
		case UP:
			if(posSelectCreate != CREATE_NAME){
				posSelectCreate -= offsetSelectCreate;
			} else {
				posSelectCreate = CREATE_BACK;
			}
			break;
		case ENTER:
			doActionCreate();
			break;
	}
}

void Menu::pollEventJoin(int key){
	switch(key){
		case DOWN:
			if (posSelectJoin != JOIN_BACK){
				posSelectJoin += offsetSelectJoin;
			} else {
						posSelectJoin = JOIN_NAME;
			}
			break;
		case UP:
			if(posSelectJoin != JOIN_NAME){
				posSelectJoin -= offsetSelectJoin;
			} else {
				posSelectJoin = JOIN_BACK;
			}
			break;
		case ENTER:
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
		    		if (menu != MAIN_MENU){
						menu = MAIN_MENU;
					}
					break;
				case SDLK_DOWN:
					switch (menu){
						case MAIN_MENU:
							pollEventMain(DOWN);
							break;
						case OPTIONS_MENU:
							pollEventOptions(DOWN);
							break;
						case CREATE_MENU:
							pollEventCreate(DOWN);
							break;
						case JOIN_MENU:
							pollEventJoin(DOWN);
							break;
					}
					break;
				case SDLK_UP:
					switch (menu){
						case MAIN_MENU:
							pollEventMain(UP);
							break;
						case OPTIONS_MENU:
							pollEventOptions(UP);
							break;
						case CREATE_MENU:
							pollEventCreate(UP);
							break;
						case JOIN_MENU:
							pollEventJoin(UP);
							break;
					}
					break;
				case SDLK_RETURN:
					switch (menu){
						case MAIN_MENU:
							pollEventMain(ENTER);
							break;
						case OPTIONS_MENU:
							pollEventOptions(ENTER);
							break;
						case CREATE_MENU:
							pollEventCreate(ENTER);
							break;
						case JOIN_MENU:
							pollEventJoin(ENTER);
							break;
					}
					break;
		    }
		}
    }
}

bool Menu::quitGame(){
	if (hasQuitGame){
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
	if (hasJoinGame){
		SDL_HideWindow(menuWindow);
	}
	return hasJoinGame;
}

void Menu::setMatches(std::vector<std::string> matches){
	vectorMatches = matches;
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
}