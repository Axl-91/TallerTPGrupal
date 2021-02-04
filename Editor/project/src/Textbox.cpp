#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>  
#include <algorithm>
#include "Textbox.h"

Textbox::Textbox(){}

void Textbox::init(SDL_Renderer* _renderer,int _x, int _y, int _textboxText,
        bool _focused, TTF_Font *_gFont, std::vector<int> opts){
    options = opts;
    gFont = _gFont;
    pos.setPosX(_x);
    pos.setPosY(_y);
    focused = _focused; 

    std::vector<int>::iterator itr= std::find(options.begin(), options.end(),_textboxText);    
     if (itr != options.cend()) {
         indexelementSelected = std::distance(options.begin(), itr);
    }    
    textboxText = std::to_string(_textboxText);
    winRenderer = _renderer;
    srctxt = {_x, _y,TXTH ,TXTW} ;    
    getTexture();
}
std::string Textbox::gettextboxText() const {
    return textboxText;
}

void Textbox::setFocus(Button &but){
    Position posB = but.getPosition();
    if(this->pos.samePos(posB)){
        focused = true;        
    } else {
        focused = false;
    }
}

void Textbox::getTexture(){
    SDL_Surface* surface = TTF_RenderText_Solid( gFont, textboxText.c_str(), textColor );

    if (!surface) {        
        std::cout << "ERROR : " << SDL_GetError()  << std::endl;
    } 

    textura = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!textura) {
        throw std::exception(); 
    }
    SDL_FreeSurface(surface);
}

void Textbox::render(){    
   SDL_Surface* surface = TTF_RenderText_Solid( gFont, textboxText.c_str(), textColor );

    if (!surface) {        
        std::cout << "ERROR : " << SDL_GetError()  << std::endl;
    } 

    textura = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!textura) {
        throw std::exception(); 
    }
    SDL_FreeSurface(surface);
    SDL_RenderCopy(winRenderer, textura, NULL, &srctxt);  
}

void Textbox::avanzar(){
    //std::cout<<textboxText;
    int elements = options.size()-1;
    if(indexelementSelected<elements){
        indexelementSelected++;
    } else{
        indexelementSelected = 0;
    }
    textboxText = std::to_string(options.at(indexelementSelected));
}

void Textbox::retroceder(){
    //std::cout<<textboxText;    
    int elements = options.size()-1;
    if(indexelementSelected==0){
        indexelementSelected = elements;
    } else{
        indexelementSelected --;
    }
    textboxText = std::to_string(options.at(indexelementSelected));
}


void Textbox::pollEvent(SDL_Event &e){    
    if(focused){
        if (e.type == SDL_KEYDOWN){ 
            switch(e.key.keysym.sym){
                case SDLK_RIGHT:
                    avanzar();
                    break;
                case SDLK_LEFT:
                    retroceder();
                    break;
                case SDLK_KP_ENTER:
                    avanzar();
                    break;
                break;
            }
        }
    }       
    
}

Textbox::~Textbox(){
    gFont = NULL;
    SDL_DestroyTexture(textura);        
}