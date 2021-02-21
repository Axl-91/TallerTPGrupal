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
    int posXGun = 0;
    int posYGun = 41;
    int posXNum = 0;
    int posYNum = 66;
    int posXFac = 25;
    int posYFac = 0;
    SpritesHandler textureHandler;
    SpritesHandler gun;
    SpritesHandler numbers;
    SpritesHandler faces;
    SpritesHandler keys;

    void getTexture();
    void renderNumber(int number, int &x, int &y);
public:
    Hud();
	Hud(const Hud &copy) = delete;
	Hud operator=(const Hud &copy) = delete;
    void setWeapon(weapon_t aWeapon);

    void setRenderer(SDL_Renderer* renderer);
    void render(int &longWin, int &highWin);
    void renderHealth(int &health);
    void renderAmmo(const int &ammo);
    void renderLife(const int &life);
    void renderScore(const int &score);
    void renderGoldenKey();
    void renderSilverKey();
    void renderFace(const int &health);
    ~Hud();
};

#endif