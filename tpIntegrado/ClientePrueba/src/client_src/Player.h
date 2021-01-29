#ifndef __PLAYER__
#define __PLAYER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "../common_src/types.h"
#include "Hud.h"
#include "./inventory/PlayerWeapon.h"
#include "inventory/Inventory.h"
// #include "weapon_t.h"
// #include "heal_t.h"
#include "../common_src/Circle.h"
// #include "SpritesHandler.h"
// #include "SDL_EventHandler.h"

#define MAX_HEALTH 100


class Player{
private:
    // SDL_EventHandler s;
    // SpritesHandler p;
    circle position;
    float angulo;
    float dx;
    float dy;
    float step;
    float distBuffer[320];
    int health;
    size_t lifes;
    size_t score;
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

    // void shoot();
    void setWeapon(player_weapons_t w);
    void getPosition(float &x, float &y);
    void getPosition(circle &c);

    void getDirection(float &x, float &y);
    void equip(weapon_t w);
    int heal(int &h);
    int reload(int &ammo);
    void updateInfo(Player_t &p);

    ~Player();
};

#endif
