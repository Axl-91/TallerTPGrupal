#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#define BUTH 16
#define BUTW 16

class Button{
private:
    void getTexture();
    void avanzar();
    void retroceder();
protected:
    SDL_Rect srcBut = {0, 0, 32, 32};
    int x, y, posxInicial,posyInicial, movs;
    const char* imgFile = "brush.png";
    SDL_Texture* textura;
    SDL_Renderer* winRenderer;    
public:
    Button();
    void setRenderer(SDL_Renderer* renderer);	    
    void pollEvent(SDL_Event &evento);    
    void render(int posX, int posY);
    ~Button();
};

#endif