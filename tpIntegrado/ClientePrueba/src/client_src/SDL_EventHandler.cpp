#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDL_EventHandler.h"

SDL_EventHandler::SDL_EventHandler(ProtectedEventQueue &q):
	q(q),
	is_running(false),
	quitGameRead(false)
{
	keyDownEvents[SDLK_1] = PLAYER_SET_WEAPON_KNIFE;
	keyDownEvents[SDLK_2] = PLAYER_SET_WEAPON_GUN;
	keyDownEvents[SDLK_3] = PLAYER_SET_WEAPON_SECONDARY;
	keyDownEvents[SDLK_UP] = PLAYER_START_MOVING_FORWARD;
	keyDownEvents[SDLK_DOWN] = PLAYER_START_MOVING_BACKWARD;
	keyDownEvents[SDLK_RIGHT] = PLAYER_START_ROTATING_RIGHT;
	keyDownEvents[SDLK_LEFT] = PLAYER_START_ROTATING_LEFT;
	keyDownEvents[SDLK_SPACE] = PLAYER_SHOOT;
	keyDownEvents[SDLK_p] = PICHIWAR;
	keyDownEvents[SDLK_u] = UNIRME;

	keyUpEvents[SDLK_UP] = PLAYER_STOP_MOVING;
	keyUpEvents[SDLK_DOWN] = PLAYER_STOP_MOVING;
	keyUpEvents[SDLK_RIGHT] = PLAYER_STOP_ROTATING;
	keyUpEvents[SDLK_LEFT] = PLAYER_STOP_ROTATING;
	keyUpEvents[SDLK_SPACE] = PLAYER_STOP_SHOOTING;
}
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
			event = keyDownEvents[SDLEvent.key.keysym.sym];
		}
		if (SDLEvent.type == SDL_KEYUP){
			event = keyUpEvents[SDLEvent.key.keysym.sym];
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
