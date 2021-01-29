#ifndef __TEXTURE_ENEMIES__
#define __TEXTURE_ENEMIES__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#include "SDLHandler.h"
#include "SpritesHandler.h"

#define LARGO 64
#define ALTO 64

class Enemies{
private:
    std::vector<std::string> EnemiesSprites = {
    "Media/EnemiesSprites/Guard01.png", "Media/EnemiesSprites/Guard02.png",
    "Media/EnemiesSprites/Guard03.png", "Media/EnemiesSprites/Guard04.png",
    "Media/EnemiesSprites/Guard05.png", "Media/EnemiesSprites/Guard06.png",
    "Media/EnemiesSprites/Guard07.png", "Media/EnemiesSprites/Guard08.png",
    };
    SpritesHandler EnemiesHandler;
    int angleEnemy = 0;
    //angleEnemy con angulo en grados
    int pos = 0;
public:
    Enemies();
    void setRenderer(SDL_Renderer* renderer);
    void setAngle(int angle);
    void setPos(int anglePlayer);
    void recortar(int x, int y, int largo = LARGO, int alto = ALTO);
    void render(int x, int y, int largo = LARGO, int alto = ALTO);
    ~Enemies();
};

#endif