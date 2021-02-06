#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Menu.h"
#include "SDLHandler.h"

Menu::Menu(): 
	mainMenu(0, 0, 320, 240, "MainMenu.png"),
	optionsMenu(0, 0, 320, 240, "OptionsMenu.png"),
	newGameMenu(0, 0, 320, 240, "JoinMenu.png"),
	selection(0, 0, 23, 33, "SelectionMenu.png")
	//joinGameMenu(0, 0, 320, 240, "NewMenu.png"),
	
{
		initialize();
		createText();
}

void Menu::createText(){
	//MEJORAR CON UN HANDLER DE TEXTOS QUIZAS?
	SDL_Surface* surfaceText;
	TTF_Font* font = TTF_OpenFont("beamweapon.ttf", 24);
	SDL_Color white = {255, 255, 255};
	SDL_Color yellow = {255, 204, 0};

	surfaceText = TTF_RenderText_Blended(font, "Edit Map", white);
	createGame = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	/*surfaceText = TTF_RenderText_Blended(font, "Join Game", white);
	joinGame = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);*/

	surfaceText = TTF_RenderText_Blended(font, "Options", white);
	optionsGame = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "Exit", white);
	exitGame = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "Resolution", white);
	resolution = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "Full Screen", white);
	fullScreen = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "On", yellow);
	on = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "Off", yellow);
	off = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "640x480", yellow);
	resOne = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "800x600", yellow);
	resTwo = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "1024x768", yellow);
	resThree = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "Go Back", white);
	back = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);
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

	SDL_SetWindowTitle(menuWindow, "Game Editor");
	SDL_RenderSetLogicalSize(menuRenderer, largo, alto);

	mainMenu.setRenderer(menuRenderer);
	optionsMenu.setRenderer(menuRenderer);
	newGameMenu.setRenderer(menuRenderer);
	//joinGameMenu.setRenderer(menuRenderer);
	selection.setRenderer(menuRenderer);
	selection.setSrc(0, 0, 23, 16);

	TTF_Init();
}

void Menu::renderTextMain(){
	SDL_Rect create_rect = {100,75,110,30};
	/*SDL_Rect join_rect = {100,100,110,30};
	SDL_Rect options_rect = {100,125,90,30};
	SDL_Rect exit_rect = {100,150,50,30};*/
	SDL_Rect options_rect = {100,100,110,30};
	SDL_Rect exit_rect = {100,125,90,30};

	SDL_RenderCopy(menuRenderer, createGame, NULL, &create_rect);
	//SDL_RenderCopy(menuRenderer, joinGame, NULL, &join_rect);
	SDL_RenderCopy(menuRenderer, optionsGame, NULL, &options_rect);
	SDL_RenderCopy(menuRenderer, exitGame, NULL, &exit_rect);
}

void Menu::renderTextOptions(){
	SDL_Rect create_rect = {100,75,55,15};
	//SDL_Rect join_rect = {100,100,55,15};
	SDL_Rect back_rect = {100,125,55,15};

	SDL_Rect res_rect = {175, 75, 45, 15};
	SDL_Rect switch_rect = {175,100,15,15};

	SDL_RenderCopy(menuRenderer, resolution, NULL, &create_rect);
	//SDL_RenderCopy(menuRenderer, fullScreen, NULL, &join_rect);
	SDL_RenderCopy(menuRenderer, back, NULL, &back_rect);

	if (winLargo == 640){
		SDL_RenderCopy(menuRenderer, resOne, NULL, &res_rect);
	} else if (winLargo == 800){
		SDL_RenderCopy(menuRenderer, resTwo, NULL, &res_rect);
	} else if (winLargo == 1024){
		SDL_RenderCopy(menuRenderer, resThree, NULL, &res_rect);
	}
	
	if (isFullScreen){
		SDL_RenderCopy(menuRenderer, on, NULL, &switch_rect);
	} else {
		SDL_RenderCopy(menuRenderer, off, NULL, &switch_rect);
	}
}

void Menu::renderMenu(){
    if (menu == MAIN){
		mainMenu.render(0, 0, 320, 240);
		selection.render(70, posSelectMain, 23, 16);
		renderTextMain();
	} else if (menu == OPTIONS){
		optionsMenu.render(0, 0 ,320 ,240);
		selection.render(70, posSelectOpt, 23, 16);
		renderTextOptions();
	}
}

void Menu::render(){
	renderMenu();
    SDL_RenderPresent(menuRenderer);
}

void Menu::doActionMain(){
	switch (posSelectMain){
		case MAIN_CREATE:
			hasEnterGame = true;
			break;
		case MAIN_OPTIONS:
			menu = OPTIONS;
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
			break;
		case OPT_FS:
			if (!isFullScreen){
				SDL_SetWindowFullscreen(menuWindow, SDL_WINDOW_FULLSCREEN);
				isFullScreen = true;
			} else {
				SDL_SetWindowFullscreen(menuWindow, 0);
				SDL_SetWindowSize(menuWindow, winLargo, winAlto);
				isFullScreen = false;
			}
			break;
		case OPT_BACK:
			menu = MAIN;
			break;
	}
}

void Menu::pollEventMain(int key){
	switch(key){
		case DOWN:
			if (posSelectMain != MAIN_EXIT){
				posSelectMain += 25;
			} else {
						posSelectMain = MAIN_CREATE;
			}
			break;
		case UP:
			if(posSelectMain != MAIN_CREATE){
				posSelectMain -= 25;
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
				posSelectOpt += 25;
			} else {
						posSelectOpt = OPT_RES;
			}
			break;
		case UP:
			if(posSelectOpt != OPT_RES){
				posSelectOpt -= 25;
			} else {
				posSelectOpt = OPT_BACK;
			}
			break;
		case ENTER:
			doActionOpt();
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
		    		if (menu != MAIN){
						menu -= 1;
					}
					break;
				case SDLK_DOWN:
					switch (menu){
						case MAIN:
							pollEventMain(DOWN);
							break;
						case OPTIONS:
							pollEventOptions(DOWN);
							break;
					}
					break;
				case SDLK_UP:
					switch (menu){
						case MAIN:
							pollEventMain(UP);
							break;
						case OPTIONS:
							pollEventOptions(UP);
							break;
					}
					break;
				case SDLK_RIGHT:
					switch (menu){
						case MAIN:
							pollEventMain(RIGHT);
							break;
						case OPTIONS:
							pollEventOptions(RIGHT);
							break;
					}
					break;
				case SDLK_LEFT:
					switch (menu){
						case MAIN:
							pollEventMain(LEFT);
							break;
						case OPTIONS:
							pollEventOptions(LEFT);
							break;
					}
					break;
				case SDLK_RETURN:
					switch (menu){
						case MAIN:
							pollEventMain(ENTER);
							break;
						case OPTIONS:
							pollEventOptions(ENTER);
							break;
					}
					break;
		    }
		}
    }
}

bool Menu::getFullScreen(){
	return isFullScreen;
}

bool Menu::quitGame(){
	if (hasQuitGame){
		SDL_HideWindow(menuWindow);
	}
    return hasQuitGame;
}

bool Menu::enterGame(){
	if (hasEnterGame){
		SDL_HideWindow(menuWindow);
	}
	return hasEnterGame;
}

Menu::~Menu(){
	SDL_DestroyTexture(createGame);
	//SDL_DestroyTexture(joinGame);
	SDL_DestroyTexture(optionsGame);
	SDL_DestroyTexture(exitGame);
	SDL_DestroyTexture(resolution);
	SDL_DestroyTexture(fullScreen);
	SDL_DestroyTexture(on);
	SDL_DestroyTexture(off);
	SDL_DestroyTexture(resOne);
	SDL_DestroyTexture(resTwo);
	SDL_DestroyTexture(resThree);

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