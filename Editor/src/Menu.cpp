#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Menu.h"
#include "SDLHandler.h"

Menu::Menu(): 
	splash(0, 0, 320, 240, "splash.png"),
	mainMenu(0, 0, 320, 240, "MainMenu.png"),
	optionsMenu(0, 0, 320, 240, "OptionsMenu.png"),
	selection(0, 0, 23, 33, "SelectionMenu.png"),
	main(0, 0, 320, 240, "OptionsMenu.png")
	
{
		initialize();
		createText();
}

void Menu::createText(){
	SDL_Surface* surfaceText;
	TTF_Font* font = TTF_OpenFont("beamweapon.ttf", 24);
	SDL_Color white = {255, 255, 255};
	SDL_Color yellow = {255, 204, 0};

	surfaceText = TTF_RenderText_Blended(font, "Create Map", white);
	createGame = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	if(createGame==NULL){
		std::cout<<"error"<<std::endl;
	}

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
	TTF_Init();

	splash.setRenderer(menuRenderer);
	mainMenu.setRenderer(menuRenderer);
	optionsMenu.setRenderer(menuRenderer);
	selection.setRenderer(menuRenderer);
	main.setRenderer(menuRenderer);

	selection.setSrc(0, 0, 23, 16);

	sett.init(mapname);
	map.init(sett,menuRenderer);
}

void Menu::renderTextMain(){
	SDL_Rect create_rect = {100,75,110,30};
	SDL_Rect options_rect = {100,100,110,30};
	SDL_Rect exit_rect = {100,125,90,30};

	SDL_RenderCopy(menuRenderer, createGame, NULL, &create_rect);	
	SDL_RenderCopy(menuRenderer, optionsGame, NULL, &options_rect);
	SDL_RenderCopy(menuRenderer, exitGame, NULL, &exit_rect);
}

void Menu::renderTextOptions(){
	SDL_Rect create_rect = {100,75,55,15};
	SDL_Rect join_rect = {100,100,55,15};
	SDL_Rect back_rect = {100,125,55,15};

	SDL_Rect res_rect = {175, 75, 45, 15};
	SDL_Rect switch_rect = {175,100,15,15};

	SDL_RenderCopy(menuRenderer, resolution, NULL, &create_rect);
	SDL_RenderCopy(menuRenderer, fullScreen, NULL, &join_rect);
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
	if (menu == SPL){
		splash.render(0,0,320,240);
    } else if (menu == MAIN){
		mainMenu.render(0, 0, 320, 240);
		selection.render(70, posSelectMain, 23, 16);
		renderTextMain();
	} else if (menu == OPTIONS){
		optionsMenu.render(0, 0 ,320 ,240);
		selection.render(70, posSelectOpt, 23, 16);
		renderTextOptions();
	} else if(menu == MAP){
		main.render(0, 0, 320, 240);
		map.render();
	}
}

void Menu::render(){
	renderMenu();
    SDL_RenderPresent(menuRenderer);
}

void Menu::doActionMain(){
	switch (posSelectMain){
		case MAIN_CREATE:
			menu = MAP;
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

int Menu::getWinWidth() const{
	return winLargo;
}

int Menu::getWinHeight() const{
	return winAlto;
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


void Menu::pollEventMain(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				hasQuitGame = true;
				break;
			case SDLK_DOWN:			   
				if (posSelectMain != MAIN_EXIT){
					posSelectMain += 25;
				} else {
					posSelectMain = MAIN_CREATE;
				}
				break;
			case SDLK_UP:
				if(posSelectMain != MAIN_CREATE){
					posSelectMain -= 25;
				} else {
					posSelectMain = MAIN_EXIT;
				}
				break;
			case SDLK_RETURN:
				doActionMain();
				break;
			}
	}
}

void Menu::pollEventSplash(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		menu = MAIN;
	}
}

void Menu::pollEventOptions(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
		case SDLK_ESCAPE:menu = MAIN;
			break;
		case SDLK_DOWN:	   
				if (posSelectOpt != OPT_BACK){
					posSelectOpt += 25;
				} else {
					posSelectOpt = OPT_RES;
				}
			break;
		case SDLK_UP:
			if(posSelectOpt != OPT_RES){
				posSelectOpt -= 25;
			} else {
				posSelectOpt = OPT_BACK;
			}
			break;
		case SDLK_RETURN:
			doActionOpt();
			break;
		}
	}
}

void Menu::pollEventMap(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
			case SDLK_ESCAPE:menu = MAIN;							
			break;
		}
	}
	map.setResolution(winLargo,winAlto);
	map.pollEvent(event);
}

void Menu::pollEvent(){
    SDL_Event event;
    if (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT ){
		    hasQuitGame = true;
	    } else{
			switch (menu){
			case SPL: pollEventSplash(event);
				break;				
			case MAIN: pollEventMain(event);
				break;
			case OPTIONS: pollEventOptions(event);
				break;
			case MAP: pollEventMap(event);
				break;
			default:
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
	SDL_DestroyTexture(optionsGame);
	SDL_DestroyTexture(exitGame);
	SDL_DestroyTexture(resolution);
	SDL_DestroyTexture(fullScreen);
	SDL_DestroyTexture(on);
	SDL_DestroyTexture(back);
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