#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Position.h"

Position::Position(){ }

void Position::init(int _x, int _y){ 
    x = _x;
    y = _y;
}
int Position::getPosX() const{
    return x;
}
int Position::getPosY() const{
    return y;
}

bool Position::samePos(Position &pos){
    if(y == pos.getPosY()){
        return true;
    } 
    return false;
}

void Position::setPosY(int _y){
    y = _y;
}  
void Position::setPosX(int _x){
    x = _x;
}  

Position::~Position(){}