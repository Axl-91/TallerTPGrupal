#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDL_EventHandler.h"

SDL_EventHandler::SDL_EventHandler(ProtectedEventQueue &q):
	q(q),
	is_running(false),
	quitGameRead(false)
{}
SDL_EventHandler::~SDL_EventHandler(){}

void SDL_EventHandler::operator()(){
	this->start();
}

void SDL_EventHandler::run(){
    is_running = true;
	event_t event;
	try{
		while(is_running){
			if(!finished())
				event = pollEvent();
		
			if(event != NO_EVENT){
				q.push(event);
			}
			sleep(1/60);
		}
	} catch (const std::exception &e){
        std::cerr << "Excepcion en SDL_EventHandler.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
	std::cout << "salgo de SDL_EventHandler.run()" << std::endl;
}

void SDL_EventHandler::stop(){
	is_running = false;
}

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
				case SDLK_p:
					event=PICHIWAR;
					// player.shoot();
	                break;
				case SDLK_u:
					event=UNIRME;
					// player.shoot();
	                break;
				break;
			}
		}
		if (SDLEvent.type == SDL_KEYUP){
			switch(SDLEvent.key.keysym.sym){
    	        case SDLK_SPACE:
					event=PLAYER_STOP_SHOOTING;
					break;
				break;
			}
		}
	}
	return event;
}

bool SDL_EventHandler::finished(){
	return quitGameRead;
}

void SDL_EventHandler::exitPollEvent(SDL_Event &SDLEvent, event_t &event){
	// if (SDLEvent.type == SDL_QUIT){
	// 	event = GAME_QUIT;
	// }
	if (SDLEvent.type == SDL_KEYDOWN && SDLEvent.key.keysym.sym == SDLK_ESCAPE){
			event = GAME_QUIT;
			// is_running = false;
			quitGameRead = true;
	}
}

bool SDL_EventHandler::isDead(){
	return !is_running;
}
