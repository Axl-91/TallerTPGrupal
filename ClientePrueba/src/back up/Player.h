#ifndef __PLAYER__
#define __PLAYER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Hud.h"
#include "inventory/PlayerWeapon.h"
#include "inventory/Inventory.h"
#include "weapon_t.h"
#include "Circle.h"

#define PI 3.14159265358979323846

typedef enum{
    FORWARD = 1,
    BACKWARD =-1
}player_orientation_t;


class Player{
private:
    circle position;
    float angulo;
    float dx;
    float dy;
    float step;
    float distBuffer[320];
    Map &mapPlayer;
    Inventory inventory;
   	Hud hudGame;

	PlayerWeapon *currentWeapon;

    SDL_Renderer* rendererPlayer;
    void renderRaycaster();
    bool objEsVisible(Vector &posObj);
    void renderObjects();
public:
//    Player();
    Player(Map &m);
    void setPos(float x, float y);
    void setMap(Map &map);
    void setRenderer(SDL_Renderer* renderer);
    void render(int largoWin, int altoWin);

    void setDirection(float x, float y);

    void shoot();
    void move(player_orientation_t &orientation);
    void setWeapon(int w);
    void rotateLeft();
    void rotateRight();
    void getPosition(float &x, float &y);
    void getPosition(circle &c);

    void getDirection(float &x, float &y);
    weapon_t equip(weapon_t w);
    ~Player();
};

#endif
