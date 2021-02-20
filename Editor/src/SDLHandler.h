#ifndef _SDL_HANDLER_H_
#define _SDL_HANDLER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class SDLHandler{
    SDL_Texture* texture;
    SDL_Renderer* rendererWin;
    std::string imgFile;
    void getTexture();

public:
    SDL_Rect src;

    SDLHandler(int posX, int posY, int length, int width, std::string iFile);
    ~SDLHandler();
    void setSrc(int posX, int posY, int largo, int ancho);
    void setRenderer(SDL_Renderer* renderer);
    void render(int posX, int posY, int largo, int ancho);
};



#endif
