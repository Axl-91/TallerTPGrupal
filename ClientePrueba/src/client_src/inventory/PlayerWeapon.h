#ifndef __TEXTURE_GUNS__
#define __TEXTURE_GUNS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../SDLHandler.h"
#include "../../common_src/types.h"
#include "../SpritesHandler.h"

//Largo y alto del arma
#define GUNL 128
#define GUNA 128

class PlayerWeapon{
protected:
    int offset = 65;
    int numAuxiliar = 0;
    // shooting_state_t &shootingState;
    shooting_state_t shootingState;

    weapon_t type;
    SpritesHandler textureHandler;

    void getTexture();
    // void disparar();
public:

    void shoot();

    PlayerWeapon(shooting_state_t &sS, std::vector<std::string> &imgs);

    PlayerWeapon(int xI, int yI, int xE, int yE);
	PlayerWeapon(const PlayerWeapon &copy) = delete;
//	PlayerWeapon operator=(const PlayerWeapon &copy) = delete;
    void setRenderer(SDL_Renderer* renderer);
    bool estaEnAccion();
    virtual void render(int posX, int posY) = 0;
    weapon_t getType();
    ~PlayerWeapon();
};

#endif