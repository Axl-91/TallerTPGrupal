#ifndef _TEXT_HANDLER_
#define _TEXT_HANDLER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

class TextHandler{
    std::vector<SDL_Texture*> vectorTextures;
    SDL_Renderer* rendererWin;
    SDL_Color colorText;
    std::vector<std::string> vectorText;
    void getTextures(SDL_Renderer* renderer, SDL_Color &color);
    void destroyTextures();
public:
    TextHandler(std::string &text);
    TextHandler(std::vector<std::string> &texts);
    void setRenderer(SDL_Renderer* renderer, SDL_Color color);
    void setSrc(int &posX, int &posY, int &length, int &height);
    void render(int &posX, int &posY, int &length, int &height, const int &pos);
    void render(int &posX, int &posY, int &length, int &height);
    void setText(std::string &newText);
    ~TextHandler();
};


#endif