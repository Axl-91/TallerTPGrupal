#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"

Game::Game(int largo, int alto,char* filename){	
    int hayError;
    winLargo = largo;
    winAlto = alto;

	hayError = SDL_Init(SDL_INIT_VIDEO);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = SDL_CreateWindowAndRenderer(winLargo, winAlto, 
		SDL_RENDERER_ACCELERATED, &window, &renderer);	

	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = TTF_Init();
	if( hayError){
		std::cout << "ERROR : " << TTF_GetError() << std::endl;		
	}
	
	SDL_SetWindowTitle(window, title);
	SDL_RenderSetLogicalSize(renderer, winLargo, winAlto);
	
	//Apertura yaml
	sett.init(filename);

	initGui();

	getTexture();
}

void Game::getTexture(){
    SDL_Surface* surface = IMG_Load(imgFile);
    if (!surface) {
        throw std::exception(); 
    }
    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    textura = SDL_CreateTextureFromSurface(renderer, surface);
    if (!textura) {
        throw std::exception(); 
    }
    SDL_FreeSurface(surface);    
}


void Game::initGui(){
	arrow.setRenderer(renderer);
	resW.init(renderer,160,145,sett.getresW());
	resH.init(renderer,160,185,sett.getresH());
	maxplayers.init(renderer,160,225,sett.getmaxlayers());
}


void Game::fill(){
	SDL_RenderClear(renderer);
	SDL_Rect destination = {0, 0, winLargo, winAlto};    
    SDL_RenderCopy(renderer, textura, NULL, &destination);  
}

void Game::exitPollEvent(SDL_Event &evento){
	if (evento.type == SDL_QUIT){
		gameOver = true;
	}
}

void Game::update(){
    SDL_Event evento;
	int xMouse, yMouse;
	SDL_GetGlobalMouseState(&xMouse,&yMouse);

	if (SDL_PollEvent(&evento)){
		exitPollEvent(evento);
		arrow.pollEvent(evento);		
		resW.pollEvent(evento);
		resH.pollEvent(evento);
		maxplayers.pollEvent(evento);
	}
}

void Game::render(){
	fill();	
	arrow.render(320, 240);
	resW.render();
	resH.render();
	maxplayers.render();
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
	SDL_Quit();
}
