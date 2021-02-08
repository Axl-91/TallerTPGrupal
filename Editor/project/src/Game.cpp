#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Game.h"
#include "SDLHandler.h"


Game::Game(bool _isFullScreen,char* filename): 
	main(0, 0, 320, 240, "OptionsMenu.png"){	
	isFullScreen = _isFullScreen;
	initialize();
	//Apertura yaml
	sett.init(filename);
	map.init(sett,renderer);	
}

void Game::initialize(){
	int hayError;
    hayError = SDL_Init(SDL_INIT_VIDEO);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = SDL_CreateWindowAndRenderer(winLargo, winAlto, 
		SDL_RENDERER_ACCELERATED, &window, &renderer);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}
	SDL_SetWindowTitle(window, "Game Editor");
	if(isFullScreen){
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}

	SDL_RenderSetLogicalSize(renderer, largo, alto);

	main.setRenderer(renderer);
}

void Game::exitPollEvent(SDL_Event &evento){
	if ((evento.type == SDL_QUIT)|| 
		(evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_ESCAPE)){
		gameOver = true;
		sett.saveChanges();
	}
}

void Game::update(){
    SDL_Event evento;

	if (SDL_PollEvent(&evento)){
		exitPollEvent(evento);
		map.pollEvent(evento);
	}	
}

void Game::render(){
	main.render(0, 0, 320, 240);
	map.render();
    SDL_RenderPresent(renderer);
}

bool Game::isGameOver(){
	return gameOver;
}

Game::~Game(){	
	SDL_DestroyTexture(textura);
	if (renderer){
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window){
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	//TTF_Quit();				
	SDL_Quit();
}
