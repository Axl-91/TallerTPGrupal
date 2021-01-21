#ifndef __TEXTURE_WALLS__
#define __TEXTURE_WALLS__

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "SDLHandler.h"
class Walls{
private:
    int srcX = 0;
    int srcY = 0;
    int offset = 64;
    SDLHandler textureHandler;
public:
    Walls();
    void setRenderer(SDL_Renderer* renderer);
    void recortar(int &posX, int &posY, int &largo, int &ancho);
    void setWall(int &num);
    void setDark();
    void render(int &posX, int &posY, int &largo, int &ancho);
    ~Walls();
};

#endif