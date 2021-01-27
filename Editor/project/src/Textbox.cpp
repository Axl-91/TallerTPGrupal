#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>  
#include "Textbox.h"

Textbox::Textbox(){
    TTF_Init();
    gFont = TTF_OpenFont( font, 30 );
    if( gFont == NULL )	{
		printf( "Failed to load SDL_ttf Error: %s\n", TTF_GetError() );		
	}
}

void Textbox::setRenderer(SDL_Renderer* renderer){
    winRenderer = renderer;
    getTexture();
}

void Textbox::init(SDL_Renderer* _renderer,int _x, int _y, int _textureText){
    std::string value = std::to_string(_textureText);
    winRenderer = _renderer;
    srctxt = {_x, _y,TXTH ,TXTW} ;    
    textureText = value== "" ? "Defecto":value;
    getTexture();
}
std::string Textbox::getTextureText() const {
    return textureText;
}

void Textbox::getTexture(){
    SDL_Surface* surface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );

    if (!surface) {        
        std::cout << "ERROR : " << SDL_GetError()  << std::endl;
    } 

    textura = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!textura) {
        throw std::exception(); 
    }
    SDL_FreeSurface(surface);
    SDL_StartTextInput();    
}

void Textbox::render(){    
   SDL_Surface* surface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );

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


void Textbox::pollEvent(SDL_Event &e){    
    if( e.type == SDL_TEXTINPUT ) {
    if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || 
        e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )    {        
        textureText += e.text.text;
        }
    }
}

Textbox::~Textbox(){
    SDL_DestroyTexture(textura);
    SDL_StopTextInput();
    TTF_CloseFont(gFont);
    TTF_Quit();
}