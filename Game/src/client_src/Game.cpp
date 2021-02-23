#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Map.h"


#define CLIENT_TIME_STEP 1000/60

//cuando se inicializa, inicia SDL
Game::Game(int &largo, int &alto, bool &fullscreen, std::vector<std::vector<int>> &lvl, ProtectedQueue<Update_t> &q):
	mapGame(lvl),
	player(mapGame),
	uQ(q),
	is_running(false),
	gameUpdater(player,uQ, mapGame, m)
{
	Update_t anUpdate;
	uQ.pop(anUpdate);

	std::cout << "este es el ID de este jugador: " << anUpdate.playerUpdate.ID << std::endl;
	player.setID(anUpdate.playerUpdate.ID);
	player.updateInfo(anUpdate.playerUpdate);

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

	if(fullscreen)
		setFullScreen();

	SDL_RenderSetLogicalSize(renderer, largoReal, altoReal);
	mapGame.setRenderer(renderer);
	player.setRenderer(renderer);
	render();
	gameSounds->playMusic(GAME_MUSIC1, 20);
}

void Game::operator()(){
	this->start();
}

void Game::run(){
	gameUpdater();
    long timeStep = CLIENT_TIME_STEP;
	is_running = true;
    try{
		while(is_running){
            auto initial = std::chrono::high_resolution_clock::now();
   std::unique_lock<std::mutex> lock(m);

//			update();
			render();
			//SLEEP?
			lock.unlock();
            auto final = std::chrono::high_resolution_clock::now();
            auto loopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
            long sleepTime = timeStep - loopDuration.count();
            if (sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
		}
    } catch (const std::exception &e){
        std::cerr << "Excepcion en Game.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
    std::cout << "sali de loop de game" << std::endl;
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

void Game::setFullScreen(){
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Game::quitGame(){
	gameOver = true;
	is_running = false;
}

void Game::stop(){
	is_running = false;
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
	if(gameUpdater.isRunning()){
		gameUpdater.stop();
		gameUpdater.join();
	}
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
