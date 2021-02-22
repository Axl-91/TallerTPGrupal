#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SpritesHandler.h"
#include "../common_src/types.h"
#include "../common_src/Vector.h"
#include <chrono>

#define MISSILE_OFFSET 600

//Clase que se ocupa de la vista de las animaciones del misil
class Missile{
    SpritesHandler spritesHandler;
    int angleEnemy = 0;
    int frame = 0;
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;

protected:
    int explodeFrames;
    int explodeFramesOffset;

    float explodeFrameTime;

public:
    Missile();
    ~Missile();

    void defineSprite(Render_missile_t &missile, Vector &posPlayer, int &sprite);
    void defineFrame(Render_missile_t &missile);
    void setRenderer(SDL_Renderer* renderer);
    void setEnemyRenderSprite(int sprite);
    void cutFromTexture(int x, int y, int largo, int alto);
    void render(int x, int y, int largo, int alto);

private:
    void defineExplodeFrame(Render_missile_t &missile);
};






#endif
