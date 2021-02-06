#ifndef __DOT__
#define __DOT__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Position.h"
#include "SDLHandler.h"

class Dot{
private:       
    static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	static const int DOT_VEL = 10;
    SDL_Rect mBox;		
	int mVelX, mVelY;

    SDL_Renderer* winRenderer;
   	SDLHandler mapDot;
    SDL_Texture* textura;
public:
    Dot();
    void pollEvent(SDL_Event &e);    
    void move();
	void setCamera(SDL_Rect& camera);
	void render(SDL_Rect& camera);
    void init(SDL_Renderer*);
    ~Dot();
};

#endif