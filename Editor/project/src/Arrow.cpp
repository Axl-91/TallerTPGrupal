#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Arrow.h"

Arrow::Arrow(){
    imgFile = "arrow.png"; 
    setSrc(0,300,w,h);
}

void Arrow::avanzar(){	
	int val;  
	switch(pos.getPosY()){
        case 300: val = 435; break;
        case 355: val = 300; break;
        case 435: val = 355; break;
        default: break;
    }
    setSrc(pos.getPosX(),val,w,h);
}

void Arrow::retroceder(){	  
    int val;  
	switch(pos.getPosY()){
        case 300: val = 355; break;
        case 355: val = 435; break;
        case 435: val = 300; break;
        default: break;
    }
    setSrc(pos.getPosX(),val,w,h);
}

void Arrow::pollEvent(SDL_Event &evento){   
    if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
			case SDLK_UP:
				avanzar();
				break;
			case SDLK_DOWN:
				retroceder();
				break;
			break;
		}
	}    
}

Arrow::~Arrow(){}