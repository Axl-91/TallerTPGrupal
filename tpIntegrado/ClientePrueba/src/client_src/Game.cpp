#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
// #include "Hud.h"
#include "Map.h"

Game::Game(int largo, int alto, std::vector<std::vector<int>> &lvl, ProtectedUpdateQueue &q): 
	mapGame(lvl),
	player(mapGame),
	uQ(q){
    int hayError;
    winLargo = largo;
    winAlto = alto;
    const char* title = "WOLFENSTEIN 3D";

	hayError = SDL_Init(SDL_INIT_VIDEO);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = SDL_CreateWindowAndRenderer(winLargo, winAlto, 
		SDL_RENDERER_ACCELERATED, &window, &renderer);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	SDL_SetWindowTitle(window, title);
	SDL_RenderSetLogicalSize(renderer, largoReal, altoReal);

	mapGame.setRenderer(renderer);
	if(uQ.isEmpty()){
		std::cout << "esto no deberia imprimirse en constructor de game" << std::endl;
	}
	Update_t anUpdate = uQ.pop();
	player.setPos(anUpdate.playerUpdate.x,anUpdate.playerUpdate.y);
	player.setRenderer(renderer);
	player.setID(anUpdate.playerUpdate.ID);
	std::cout << "este es el ID de este jugador: " << anUpdate.playerUpdate.ID << std::endl;
}

void Game::update(){
	if(uQ.isEmpty()){
		return;
		// sleep(1/60);
	}
	Update_t anUpdate = uQ.pop();

	updatePlayer(anUpdate.playerUpdate);
	if(anUpdate.mapChangeAvailable == true)
		updateMap(anUpdate.mapChange);
}
void Game::updatePlayer(Player_t &p){
	// std::cout << "este es el ID de este jugador: " << anUpdate.playerUpdate.ID << std::endl;

	if(p.ID == player.getID()){
		player.updateInfo(p);
		return;
	}
	mapGame.updateEnemy(p);
}

void Game::fill(){
    /*Dibuja la pantalla en gris claro y luego dibuja
    desde la mitad para arriba en gris oscuro */
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);

	SDL_RenderClear(renderer);
	
    SDL_Rect rect = {0,0, largoReal, (altoReal-40)/2};
	SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}
/*
void Game::setFullScreen(){
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}*/

void Game::quitGame(){
	gameOver = true;
}


void Game::render(){
	fill();
	player.render(320, 240);
    SDL_RenderPresent(renderer);
}

bool Game::isGameOver(){
	return gameOver;
}

SDL_Renderer* Game::getRenderer(){
	return renderer;
}

Game::~Game(){
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

void Game::updateMap(Map_change_t &aMapChange){
	mapGame.update(aMapChange);
}
