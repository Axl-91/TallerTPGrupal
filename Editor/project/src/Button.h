#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Position.h"

class Button{
private:
    void getTexture();
protected:
    int h = 50;
    int w = 50;
    SDL_Rect srcBut = {0, 0, 32, 32};    
    const char* imgFile = "brush.png";
    SDL_Texture* textura;
    SDL_Renderer* winRenderer;
    Position pos;    
public:    
    Button();
    void setSrc(int _x, int _y, int _w, int _h);
    Position getPosition() const;
    void init(SDL_Renderer* renderer);	    
    void render(int posX, int posY);
    ~Button();
};

#endif