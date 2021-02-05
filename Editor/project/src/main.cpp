#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "Menu.h"
#include <string>
#include "Game.h"


int main(int argc, char* argv[]){
	Menu menu;

	while (!menu.quitGame() && !menu.enterGame()){
		menu.pollEvent();
		menu.render();
		SDL_Delay(10); 
	}
	if (menu.quitGame()){
		return 0;
	}		
	Game game(menu.getFullScreen(),argv[1]);	
	while (!game.isGameOver()){
		game.update();
		game.render();
		SDL_Delay(10); 
	}	
	return 0;
}
