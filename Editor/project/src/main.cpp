#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Game.h"


int main(int argc, char* argv[]){		
	Game game(640, 480,argv[1]);	
	while (!game.isGameOver()){
		game.update();
		game.render();
		SDL_Delay(10); 
	}	
	return 0;
}
