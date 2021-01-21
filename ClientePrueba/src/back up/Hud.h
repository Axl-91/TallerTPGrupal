#ifndef __TEXTURE_HUD__
#define __TEXTURE_HUD__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDLHandler.h"
#include "weapon_t.h"
//Largo y alto del HUD
#define HUDL 320
#define HUDA 40
//Largo y alto del arma en HUD
#define HGUNL 48
#define HGUNA 23

class Hud{
private:
    int offsetGun = 49;
    SDL_Rect srcNumber = {0, 0, 0, 0};
    SDL_Rect srcKey = {0, 0, 0, 0};

    SDLHandler textureHandler;
    SDLHandler gun;

    void getTexture();
public:
    Hud();
	Hud(const Hud &copy) = delete;
	Hud operator=(const Hud &copy) = delete;
    void setWeapon(weapon_t w);

    void setRenderer(SDL_Renderer* renderer);
    void render(int largoWin, int altoWin);
    ~Hud();
};

#endif