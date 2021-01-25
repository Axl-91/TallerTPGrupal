#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDL_EventHandler.h"

SDL_EventHandler::SDL_EventHandler(){}
SDL_EventHandler::~SDL_EventHandler(){}


event_t SDL_EventHandler::pollEvent(){
    SDL_Event SDLEvent;
	event_t event=NO_EVENT;

	if (SDL_PollEvent(&SDLEvent)){
		//POLL EVENT PLAYER
		exitPollEvent(SDLEvent, event);		
		if (SDLEvent.type == SDL_KEYDOWN){
			switch(SDLEvent.key.keysym.sym){
    	        case SDLK_1:
					event=PLAYER_SET_WEAPON_KNIFE;
					// player.setWeapon(1);
					break;
            	case SDLK_2:
					event=PLAYER_SET_WEAPON_GUN;
					// player.setWeapon(2);
					break;
	            case SDLK_3:
					event=PLAYER_SET_WEAPON_SECONDARY;
					// player.setWeapon(3);
					break;
				case SDLK_UP:
					event=PLAYER_MOVE_FORWARD;
					// movePlayer(FORWARD);
					break;
				case SDLK_DOWN:
					event=PLAYER_MOVE_BACKWARD;
					// movePlayer(BACKWARD);
					break;
				case SDLK_RIGHT:
					event=PLAYER_ROTATE_RIGHT;
					// player.rotateRight();
					break;
				case SDLK_LEFT:
					event=PLAYER_ROTATE_LEFT;
					// player.rotateLeft();
					break;
            	case SDLK_SPACE:
					event=PLAYER_SHOOT;
					// player.shoot();
	                break;
				break;
			}
		}
	}
	return event;
}


void SDL_EventHandler::exitPollEvent(SDL_Event &SDLEvent, event_t &event){
	if (SDLEvent.type == SDL_QUIT){
		event = GAME_QUIT;
	}
	if (SDLEvent.type == SDL_KEYDOWN && SDLEvent.key.keysym.sym == SDLK_ESCAPE){
			event = GAME_QUIT;
	}
}
