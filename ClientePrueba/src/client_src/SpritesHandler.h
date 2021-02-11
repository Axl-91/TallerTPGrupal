#ifndef __SPRITE_HANDLER__
#define __SPRITE_HANDLER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

#define SIZE 64

class SpritesHandler{
private:
    SDL_Renderer* rendererWin;
    std::vector<std::string> imgFiles;
    void getTextures(SDL_Renderer* renderer);
    void destroyTextures();
    std::vector<SDL_Texture*> texturas;
public:
    SDL_Rect src;
    SpritesHandler(std::string file, int largo = SIZE, int alto = SIZE);
    SpritesHandler(std::vector<std::string> &iFiles, int largo = SIZE, int alto = SIZE);
    void setRenderer(SDL_Renderer* renderer);
    ~SpritesHandler();
    void setSrc(int posX, int posY, int largo, int alto);
    void setPos(int posX, int posY);
    void setSize(int largo, int alto);
    void render(int posX, int posY, int largo, int alto, int text);
    void render(int posX, int posY, int largo, int alto);
};

#endif