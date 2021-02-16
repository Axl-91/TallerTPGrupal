#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include "Menu.h"

int main(int argc, char* argv[]){
	Menu menu;

	while (!menu.quitGame()){
		menu.pollEvent();
		menu.render();
		SDL_Delay(10); 
	}	
	return 0;
}
