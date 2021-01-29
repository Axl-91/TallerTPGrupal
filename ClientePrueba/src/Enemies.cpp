#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Enemies.h"
#include "Install.h"

Enemies::Enemies(): EnemiesHandler(EnemiesSprites){
}

void Enemies::setRenderer(SDL_Renderer* renderer){
    EnemiesHandler.setRenderer(renderer);
}

void Enemies::setAngle(int angle){
    angleEnemy = angle;
}

void Enemies::setPos(int anglePlayer){
    //anglePlayer con angulo en grados
    int angleDif = abs(anglePlayer - angleEnemy);
    if (angleDif == 0){
        pos = 0;
    } else if (angleDif > 0 && angleDif < 90){
        pos = 1;
    } else if (angleDif == 90){
        pos = 2;
    } else if (angleDif > 90 && angleDif < 180){
        pos = 3;
    } else if (angleDif == 180){
        pos = 4;
    } else if (angleDif > 180 && angleDif < 270){
        pos = 5;
    } else if (angleDif == 270){
        pos = 6;
    } else if (angleDif > 270 && angleDif < 360){
        pos = 7;
    }
}

void Enemies::recortar(int x, int y, int largo, int alto){
    EnemiesHandler.setSrc(x, y, largo,alto);
}

void Enemies::render(int x, int y, int largo, int alto){
    EnemiesHandler.render(x, y, largo, alto, pos);
}

Enemies::~Enemies(){}
