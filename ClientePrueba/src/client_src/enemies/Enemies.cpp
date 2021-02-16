#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Enemies.h"
#include "ESHGuard.h"
#include "ESHHound.h"
#include "ESHOfficial.h"
#include "ESHSS.h"
#include "ESHMutant.h"
//#include "Install.h"

Enemies::Enemies(){
   enemySpriteHandler[HOUND] = new ESHHound();
   enemySpriteHandler[GUARD] = new ESHGuard();
   enemySpriteHandler[OFFICIAL] = new ESHOfficial();
   enemySpriteHandler[SS] = new ESHSS();
   enemySpriteHandler[MUTANT] = new ESHMutant();
}


Enemies::~Enemies(){
    for(auto eSH: enemySpriteHandler)
        delete eSH.second;
}

void Enemies::setRenderer(SDL_Renderer* renderer){
    for(auto eSH: enemySpriteHandler)
        eSH.second->setRenderer(renderer);
}

void Enemies::defineSprite(Enemy_t &enemy, Vector &posPlayer, int &sprite){
    enemySpriteHandler[enemy.type]->defineSprite(enemy, posPlayer, sprite);
    sprite += 100*enemy.type;
}

void Enemies::defineFrame(Enemy_t &enemy){
    enemySpriteHandler[enemy.type]->defineFrame(enemy);
}

void Enemies::setEnemyRenderSprite(int sprite){
    int aux = (int) sprite/100;
    type = (enemy_type_t) aux;
    enemySpriteHandler[type]->setEnemyRenderSprite(sprite%100);
}

void Enemies::cutFromTexture(int x, int y, int largo, int alto){
    enemySpriteHandler[type]->cutFromTexture(x, y, largo, alto);
}

void Enemies::render(int x, int y, int largo, int alto){
    enemySpriteHandler[type]->render(x, y, largo, alto);
}

