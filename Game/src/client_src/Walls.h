#ifndef __TEXTURE_WALLS__
#define __TEXTURE_WALLS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SpritesHandler.h"

class Walls{
private:
    int srcX = 0;
    int srcY = 0;
    int offset = 64;
    std::string fileWalls = "Media/Walls/walls.png";
    int wall;
    SpritesHandler textureHandler;
public:
    Walls();
    void setRenderer(SDL_Renderer* renderer);
    void cutFromTexture(int &posX, int &posY, int &length, int &height);
    void setWall(int &num);
    void setDark();
    void render(int &posX, int &posY, int &length, int &height);
    ~Walls();
};

#endif