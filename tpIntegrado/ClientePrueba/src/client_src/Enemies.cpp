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

void Enemies::defineSprite(Player_t enemy, Vector &posPlayer, int &sprite){
    //anglePlayer con angulo en grados
    Vector enemyPos(enemy.x, enemy.y);
    Vector aux(posPlayer-enemyPos);

    int angleDif = (enemy.ang+aux.getAngle())*180/3.1415;
    // std::cout<<"player ang: "<<posPlayer.getAngle()<<std::endl;
    // std::cout<<"enemy ang: "<<enemy.pos.getAngle()<<std::endl;

    if(angleDif>=360)
        angleDif-=360;
    else if(angleDif<0)
        angleDif+=360;

    if (angleDif <= 22.5 && angleDif >= 0||angleDif <=360 && angleDif >337.5){
        sprite = 0;
    } else if (angleDif > 22.5 && angleDif <= 67.5){
        sprite = 1;
    } else if (angleDif > 67.5 && angleDif <= 112.5){
        sprite = 2;
    } else if (angleDif > 112.5 && angleDif <= 157.5){
        sprite = 3;
    } else if (angleDif > 157.5 && angleDif <= 202.5){
        sprite = 4;
    } else if (angleDif > 202.5 && angleDif <= 247.5){
        sprite = 5;
    } else if (angleDif > 247.5 && angleDif <= 292.5){
        sprite = 6;
    } else if (angleDif > 292.5  && angleDif <= 337.5){
        sprite = 7;
        }
    // if (angleDif <= 22.5 && angleDif >= 0||angleDif <=360 && angleDif >337.5){
    //     sprite = 0;
    // } else if (angleDif > 22.5 && angleDif <= 67.5){
    //     sprite = 7;
    // } else if (angleDif > 67.5 && angleDif <= 112.5){
    //     sprite = 6;
    // } else if (angleDif > 112.5 && angleDif <= 157.5){
    //     sprite = 5;
    // } else if (angleDif > 157.5 && angleDif <= 202.5){
    //     sprite = 4;
    // } else if (angleDif > 202.5 && angleDif <= 247.5){
    //     sprite = 3;
    // } else if (angleDif > 247.5 && angleDif <= 292.5){
    //     sprite = 2;
    // } else if (angleDif > 292.5  && angleDif <= 337.5){
    //     sprite = 1;
    //     }
    // std::cout<<"dif angulo: "<<angleDif<<std::endl;
    // std::cout<<"sprite: "<<sprite+1<<std::endl;

    sprite+=100;
}

void Enemies::setEnemy(int e){
    pos=e;
}

void Enemies::recortar(int x, int y, int largo, int alto){
    EnemiesHandler.setSrc(x, y, largo,alto);
}

void Enemies::render(int x, int y, int largo, int alto){
    EnemiesHandler.render(x, y, largo, alto, pos-100);
}

Enemies::~Enemies(){}
