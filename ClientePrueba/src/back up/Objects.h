#ifndef __TEXTURE_OBJECTS__
#define __TEXTURE_OBJECTS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#include "SDLHandler.h"
#define LADO 64

class Objects{
private:
    int srcX = 0;
    int srcY = 0;
    int offset = 65;
    SDLHandler textureHandler;
public:
    Objects();
    void setRenderer(SDL_Renderer* renderer);
    void setObject(int num);
    void recortar(int x, int y, int largo = LADO, int alto = LADO);
    void render(int x, int y, int largo = LADO, int alto = LADO);
    ~Objects();
};

#endif