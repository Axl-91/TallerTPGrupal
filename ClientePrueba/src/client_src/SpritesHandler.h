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
    std::vector<SDL_Texture*> texturesVector;
    SDL_Rect src;
    void getTextures(SDL_Renderer* renderer);
    void destroyTextures();
public:
    SpritesHandler(const std::string &file, const int &lenght = SIZE, const int &height = SIZE);
    SpritesHandler(std::vector<std::string> &iFiles, const int &lenght = SIZE, const int &height = SIZE);
    void setRenderer(SDL_Renderer* renderer);
    void setSrc(int &posX, int &posY, const int &lenght, const int &height);
    int getPosX();
    int getPosY();
    void setPos(int &posX, int &posY);
    void setSize(int &lenght, int &height);
    void render(int &posX, int &posY, const int &lenght, const int &height, const int &text);
    void render(int &posX, int &posY, const int &lenght, const int &height);
    ~SpritesHandler();
};

#endif