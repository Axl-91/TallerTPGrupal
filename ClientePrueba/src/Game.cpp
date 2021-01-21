#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Hud.h"
#include "Map.h"


Game::Game(int largo, int alto, std::vector<std::vector<int>> &lvl): 
	colMap(lvl),
	mapGame(lvl),
	player(mapGame){
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

	player.setPos(96,96);
	player.setRenderer(renderer);
}

void Game::setFullScreen(){
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
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

void Game::exitPollEvent(SDL_Event &evento){
	if (evento.type == SDL_QUIT){
		gameOver = true;
	}
	if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
			case SDLK_ESCAPE:
				gameOver = true;
		}
	}
}


void Game::movePlayer(player_orientation_t orientation){
	float dx;
	float dy;
	circle playerPos;
	int collidableIdentifier;
	player.getPosition(playerPos);
	player.getDirection(dx,dy);
	dx*=orientation;
	dy*=orientation;

	std::vector<Collidable*> col;
	colMap.detectCollision(playerPos,dx,dy,col);
	for(size_t i=0;i<col.size();i++){
		if(col[i]->isInside(playerPos)==false){
			collidableIdentifier=col[i]->collide(player);
			playerPos.x+=dx;
			playerPos.y+=dy;
			handleCollision(playerPos, collidableIdentifier);
		}
	}
	player.move(orientation);
}

void Game::handleCollision(circle &playerPos, int c){
	Collidable *maker;
	if(c>=400||c%100==0)
		return;

	colMap.erase(playerPos);
	mapGame.eraseObj(playerPos.x,playerPos.y);
	if(c>102&&c<200){
	 	colMap.insert(playerPos.x, playerPos.y, c);
		mapGame.insertWeapon(playerPos.x, playerPos.y, c);
	}
}


void Game::pollEvent(){
    SDL_Event evento;

	if (SDL_PollEvent(&evento)){
		//POLL EVENT PLAYER
		exitPollEvent(evento);		
		if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
            case SDLK_1:
				player.setWeapon(1);
				break;
            case SDLK_2:
				player.setWeapon(2);
				break;
            case SDLK_3:
				player.setWeapon(3);
				break;
			case SDLK_UP:
				movePlayer(FORWARD);
				break;
			case SDLK_DOWN:
				movePlayer(BACKWARD);
				break;
			case SDLK_RIGHT:
				player.rotateRight();
				break;
			case SDLK_LEFT:
				player.rotateLeft();
				break;
            case SDLK_SPACE:
				player.shoot();
                break;
			break;

		}
	}

	}
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
