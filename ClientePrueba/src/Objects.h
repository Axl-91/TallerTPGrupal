#ifndef __TEXTURE_OBJECTS__
#define __TEXTURE_OBJECTS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#include "SDLHandler.h"
#include "SpritesHandler.h"

#define LARGO 64
#define ALTO 64

class Objects{
private:
    std::vector<std::string> ObjectsSprites = {
    "Media/ObjectsSprites/Obj01.png", "Media/ObjectsSprites/Obj02.png",
    "Media/ObjectsSprites/Obj03.png", "Media/ObjectsSprites/Obj04.png",
    "Media/ObjectsSprites/Obj05.png", "Media/ObjectsSprites/Obj06.png",
    "Media/ObjectsSprites/Obj07.png", "Media/ObjectsSprites/Obj08.png",
    "Media/ObjectsSprites/Obj09.png", "Media/ObjectsSprites/Obj10.png",
    "Media/ObjectsSprites/Obj11.png", "Media/ObjectsSprites/Obj12.png",
    "Media/ObjectsSprites/Obj13.png", "Media/ObjectsSprites/Obj14.png",
    "Media/ObjectsSprites/Obj15.png", "Media/ObjectsSprites/Obj16.png",
    "Media/ObjectsSprites/Obj17.png", "Media/ObjectsSprites/Obj18.png",
    "Media/ObjectsSprites/Obj19.png", "Media/ObjectsSprites/Obj20.png",
    "Media/ObjectsSprites/Obj21.png", "Media/ObjectsSprites/Obj22.png",
    "Media/ObjectsSprites/Obj23.png", "Media/ObjectsSprites/Obj24.png",
    "Media/ObjectsSprites/Obj25.png", "Media/ObjectsSprites/Obj26.png",
    "Media/ObjectsSprites/Obj27.png", "Media/ObjectsSprites/Obj28.png",
    "Media/ObjectsSprites/Obj29.png", "Media/ObjectsSprites/Obj29.png",
    "Media/ObjectsSprites/Obj30.png", "Media/ObjectsSprites/Obj31.png",
    "Media/ObjectsSprites/Obj32.png", "Media/ObjectsSprites/Obj33.png",
    "Media/ObjectsSprites/Obj34.png", "Media/ObjectsSprites/Obj35.png",
    };
    SpritesHandler objHandler;
    int objSelected = 0;
public:
    Objects();
    void setRenderer(SDL_Renderer* renderer);
    void setObject(int num);
    void recortar(int x, int y, int largo = LARGO, int alto = ALTO);
    void render(int x, int y, int largo = LARGO, int alto = ALTO);
    ~Objects();
};

#endif