#ifndef __TEXTBOX__
#define __TEXTBOX__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "Gui.h"

#define TXTH 32
#define TXTW 32

class Textbox{
private:    
    SDL_Rect srctxt;
    SDL_Color textColor = { 255, 255, 255, 255 };
    TTF_Font *gFont = NULL;
    std::string textureText;
    const char* font = "wolfenstein.ttf";
    int x;
    int y;  
    SDL_Texture* textura = NULL;
    SDL_Renderer* winRenderer;
    bool changed;    
    void getTexture();
public:
    Textbox();
    void init(SDL_Renderer* _renderer, int _x, int _y, int  _textureText);
    std::string getTextureText()const;
    void setRenderer(SDL_Renderer* renderer);	
    void pollEvent(SDL_Event &evento);    
    void render();
    ~Textbox();
};

#endif