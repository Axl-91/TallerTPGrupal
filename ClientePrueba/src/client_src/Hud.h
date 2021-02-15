#ifndef __TEXTURE_HUD__
#define __TEXTURE_HUD__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SpritesHandler.h"
#include "../common_src/types.h"

//Largo y alto del HUD
#define HUDL 320
#define HUDA 40
//Largo y alto del arma en HUD
#define HGUNL 48
#define HGUNA 24
//Largo y alto del numero en HUD
#define HNUML 8
#define HNUMA 16
//Largo y alto de llave en HUD
#define HKEYL 8
#define HKEYA 16
//Largo y alto de las caras
#define HFACEL 24
#define HFACEA 32

class Hud{
private:
    int offsetGun = 49;
    int offsetNum = 9;
    SDL_Rect srcKey = {196, 41, HKEYL, HKEYA};
    SpritesHandler textureHandler;
    SpritesHandler gun;
    SpritesHandler numbers;
    SpritesHandler faces;

    void getTexture();
    void renderNumber(int number, int x, int y);
public:
    Hud();
	Hud(const Hud &copy) = delete;
	Hud operator=(const Hud &copy) = delete;
    void setWeapon(weapon_t aWeapon);

    void setRenderer(SDL_Renderer* renderer);
    void render(int longWin, int highWin);
    void renderHealth(int health);
    void renderAmmo(int ammo);
    void renderLife(int life);
    void renderScore(int score);
    void renderFace(int health);
    ~Hud();
};

#endif