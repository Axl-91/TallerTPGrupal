#ifndef __PLAYER__
#define __PLAYER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "../common_src/types.h"
#include "Hud.h"
#include "inventory/PlayerWeapon.h"
#include "inventory/Inventory.h"
#include "SpritesHandler.h"

#define MAX_HEALTH 100


class Player{
private:
    circle position;
    float angPlayer;
    float dx;
    float dy;
    float step;
    float distBuffer[320];
    int health;
    bool blueKey;
    bool goldKey;   

    size_t lifes;
    size_t score;
    Map &mapPlayer;
    Inventory inventory;
   	Hud hudGame;
    size_t ID;
    shooting_state_t shootingState;
	PlayerWeapon *currentWeapon;

    SDL_Renderer* rendererPlayer;
    void renderRaycaster();
    bool objIsVisible(Vector &posObj);
    void renderObjects();
public:
    Player(Map &m);
    void setPos(float x, float y);
    void setMap(Map &map);
    void setRenderer(SDL_Renderer* renderer);
    void render(int longWin, int highWin);

    void setDirection(float x, float y);

    void setWeapon(player_weapons_t w);
    void getPosition(float &x, float &y);
    void getPosition(circle &c);
    void getDirection(float &x, float &y);
    void equip(weapon_t w);
    int heal(int &h);
    int reload(int &ammo);
    void updateInfo(Player_t &p);
    size_t getID();
    void setID(size_t newID);
    void shoot();
    ~Player();
};

#endif
