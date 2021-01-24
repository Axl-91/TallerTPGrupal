#ifndef _SDL_EVENT_HANDLER_H_
#define _SDL_EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum{
    NO_EVENT,
    PLAYER_SET_WEAPON_KNIFE,
    PLAYER_SET_WEAPON_GUN,
    PLAYER_SET_WEAPON_SECONDARY,
    PLAYER_MOVE_FORWARD,
    PLAYER_MOVE_BACKWARD,
    PLAYER_ROTATE_RIGHT,
    PLAYER_ROTATE_LEFT,
    PLAYER_SHOOT,
    GAME_QUIT
}event_t;


class SDL_EventHandler{

public:
    SDL_EventHandler();
    ~SDL_EventHandler();
    event_t pollEvent();
    void exitPollEvent(SDL_Event &SDLEvent, event_t &event);

};





#endif