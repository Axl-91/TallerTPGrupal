#ifndef __TEXTURE_GUNS__
#define __TEXTURE_GUNS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include "../SpritesHandler.h"
#include "../../common_src/types.h"
#include "../SpritesHandler.h"
#include "../SDL_Sounds.h"

//Largo y alto del arma
#define GUNL 128
#define GUNA 128

#define SDL_RENDER_WEAPON_POS_X 96
#define SDL_RENDER_WEAPON_POS_Y 72
#define SDL_RENDER_WEAPON_OFFSET 65

class PlayerWeapon{
protected:
    int offset;
    int frameAuxiliar;
    int posXWeapon;
    int posYWeapon;
    shooting_state_t shootingState;
    weapon_t type;
    SpritesHandler textureHandler;
    SDL_Sounds* gunSounds = SDL_Sounds::getInstance();
    bool soundOn = false;
    float frameTime;
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;

    void getTexture();

public:
    void shoot(shooting_state_t sS);
    PlayerWeapon(shooting_state_t &sS, std::vector<std::string> &imgs);
    PlayerWeapon(int xI, int yI, int xE, int yE);
	PlayerWeapon(const PlayerWeapon &copy) = delete;
    void setRenderer(SDL_Renderer* renderer);
    bool estaEnAccion();
    virtual void render(int posX, int posY) = 0;
    weapon_t getType();
    ~PlayerWeapon();
};

#endif