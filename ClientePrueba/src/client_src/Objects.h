#ifndef __TEXTURE_OBJECTS__
#define __TEXTURE_OBJECTS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common_src/Vector.h"
#include "FilesHandler.h"
#include "SpritesHandler.h"

#define LONG 64
#define HIGH 64

class Objects{
private:
    std::string fileObj = "Media/ObjectsSprites/Objects.txt";
    FilesHandler objectsFiles;
    std::vector<std::string> objectsSprites;
    SpritesHandler objHandler;
    int objSelected = 0;
public:
    Objects();
    void setRenderer(SDL_Renderer* renderer);
    void setObject(int &num);
    void cutFromTexture(int &x, int &y, const int &length = LONG, const int &height = HIGH);
    void render(int &x, int &y, const int &length = LONG, const int &height = HIGH);
    ~Objects();
};

#endif