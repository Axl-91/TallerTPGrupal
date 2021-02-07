#ifndef __TEXTURE_OBJECTS__
#define __TEXTURE_OBJECTS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common_src/Vector.h"
// #include "SDLHandler.h"
#include "SpritesHandler.h"

#define LARGO 64
#define ALTO 64



class Objects{
private:
    std::vector<std::string> ObjectsSprites = {
    "Media/ObjectsSprites/ObjCollect1.png", 
    "Media/ObjectsSprites/ObjCollect2.png", 
    "Media/ObjectsSprites/ObjCollect3.png", 
    "Media/ObjectsSprites/ObjCollect4.png", 
    "Media/ObjectsSprites/ObjCollect5.png", 
    "Media/ObjectsSprites/ObjCollect6.png", 
    "Media/ObjectsSprites/ObjCollect7.png", 
    "Media/ObjectsSprites/ObjCollect8.png", 
    "Media/ObjectsSprites/ObjCollect9.png", 
    "Media/ObjectsSprites/ObjCollect10.png", 
    "Media/ObjectsSprites/ObjCollect11.png", 
    "Media/ObjectsSprites/ObjCollect12.png", 
    "Media/ObjectsSprites/ObjCollect13.png", 
    "Media/ObjectsSprites/ObjInmov1.png", 
    "Media/ObjectsSprites/ObjInmov2.png", 
    "Media/ObjectsSprites/ObjInmov3.png", 
    "Media/ObjectsSprites/ObjInmov4.png", 
    "Media/ObjectsSprites/ObjInmov5.png", 
    "Media/ObjectsSprites/ObjInmov6.png", 
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