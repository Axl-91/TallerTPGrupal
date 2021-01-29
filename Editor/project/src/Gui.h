#ifndef _GUI__
#define _GUI_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Gui{
protected:
    SDL_Texture* textura;
    SDL_Renderer* rendererWin;
    std::string imgFile;
    void getTexture();
public:
    Gui(int posX, int posY, int length, int width);    
    ~Gui();
    void setSrc(int posX, int posY, int largo, int ancho);
    void setRenderer(SDL_Renderer* renderer);
    virtual void render(int posX, int posY, int largo, int ancho) = 0;
};

#endif
