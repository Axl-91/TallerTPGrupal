#ifndef _Collidable_H_
#define _Collidable_H_

#include <iostream>
#include "../serverPlayer.h"
#include "../../common_src/Circle.h"
#include "../../common_src/Vector.h"
#include "../../common_src/types.h"


//
//Clase padre que se ocupa del manejo de colisiones
//Los Colidable se subdividen segun el comportamiento de la colision:
//-Collectible (recolectable): se levanta del mapa (armas, llaves, etc..-)
//-Movable (movible): la colision implica un movimiento del objeto (puertas)
//-Inmovable: paredes y objetos inamovibles
class Collidable{
protected:
    float xInit;
    float xEnd;
    float yInit;
    float yEnd;
    
public:
    Collidable(){};
    Collidable(float xI, float yI, float xE, float yE);
    ~Collidable();

    bool isInside(circle &c);
    bool isInRectangle(float xI, float yI, float xE, float yE);
    virtual bool detectCollision(circle &c, float dX,float dY)=0;
    bool detectCollision(float x, float y, float dX,float dY);
    virtual int collide(ServerPlayer &p) = 0;
    Collidable& operator=(Collidable const &other); 
    friend std::ostream & operator<< (std::ostream &os, Collidable &c);

    Collidable* makeCollidable(int xI, int yI, int cellWidth, int opt);
};

#endif
