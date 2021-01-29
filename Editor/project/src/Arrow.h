#ifndef __ARROW__
#define __ARROW__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Button.h"

class Arrow : public Button{   
    private:        
        void avanzar();
        void retroceder();
    public:
        Arrow();
        void pollEvent(SDL_Event &evento);    
        ~Arrow();
};

#endif