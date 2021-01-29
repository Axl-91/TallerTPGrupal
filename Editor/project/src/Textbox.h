#ifndef __TEXTBOX__
#define __TEXTBOX__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "Gui.h"
#include "Position.h"
#include "Button.h"

#define TXTH 30
#define TXTW 60

class Textbox{
private:    
    SDL_Rect srctxt;
    SDL_Color textColor = { 100, 100, 100, 255 };
    TTF_Font *gFont = NULL;
    std::string textboxText;    
    Position pos;
    SDL_Texture* textura = NULL;
    SDL_Renderer* winRenderer;
    std::vector<int> options;
    int indexelementSelected =0;
    bool focused;    
    void getTexture();
    void avanzar();
    void retroceder();
public:
    Textbox();
    void init(SDL_Renderer* _renderer, int _x, int _y, int  _textboxText, 
                bool focused,TTF_Font *_gFont,std::vector<int> opts);
    void setFocus(Button &but);
    std::string gettextboxText()const;
    void pollEvent(SDL_Event &evento);    
    void render();
    ~Textbox();
};

#endif