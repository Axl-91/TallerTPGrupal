#ifndef _asd_
#define _asd_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class SpritesHandler{
    SDL_Renderer* rendererWin;
    std::vector<std::string> imgFiles;
    void getTextures(SDL_Renderer* renderer);
    void destroyTextures();
    std::vector<SDL_Texture*> texturas;
    SDL_Rect src;

public:

    SpritesHandler(){}
    SpritesHandler(std::vector<std::string> &iFiles);
    void setRenderer(SDL_Renderer* renderer);
    ~SpritesHandler();
    void render(int posX, int posY, int largo, int ancho, int text);
};


#endif