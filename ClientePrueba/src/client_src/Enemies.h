#ifndef __TEXTURE_ENEMIES__
#define __TEXTURE_ENEMIES__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common_src/types.h"
#include "../common_src/Vector.h"
#include "SDLHandler.h"
#include "SpritesHandler.h"

#define LARGO 64
#define ALTO 64


#define FRAME_OFFSET 8
#define GUARD_MOVEMENT_FRAMES 5
#define GUARD_DEAD_OFFSET 40


//Clase que se ocupa del renderizado de enemigos
class Enemies{
private:
    std::vector<std::string> EnemiesSprites = {
    "Media/EnemiesSprites/Guard01.png", "Media/EnemiesSprites/Guard02.png",
    "Media/EnemiesSprites/Guard03.png", "Media/EnemiesSprites/Guard04.png",
    "Media/EnemiesSprites/Guard05.png", "Media/EnemiesSprites/Guard06.png",
    "Media/EnemiesSprites/Guard07.png", "Media/EnemiesSprites/Guard08.png",
    "Media/EnemiesSprites/Guard09.png", "Media/EnemiesSprites/Guard10.png",
    "Media/EnemiesSprites/Guard11.png", "Media/EnemiesSprites/Guard12.png",
    "Media/EnemiesSprites/Guard13.png", "Media/EnemiesSprites/Guard14.png",
    "Media/EnemiesSprites/Guard15.png", "Media/EnemiesSprites/Guard16.png",
    "Media/EnemiesSprites/Guard17.png", "Media/EnemiesSprites/Guard18.png",
    "Media/EnemiesSprites/Guard19.png", "Media/EnemiesSprites/Guard20.png",
    "Media/EnemiesSprites/Guard21.png", "Media/EnemiesSprites/Guard22.png",
    "Media/EnemiesSprites/Guard23.png", "Media/EnemiesSprites/Guard24.png",
    "Media/EnemiesSprites/Guard25.png", "Media/EnemiesSprites/Guard26.png",
    "Media/EnemiesSprites/Guard27.png", "Media/EnemiesSprites/Guard28.png",
    "Media/EnemiesSprites/Guard29.png", "Media/EnemiesSprites/Guard30.png",
    "Media/EnemiesSprites/Guard31.png", "Media/EnemiesSprites/Guard32.png",
    "Media/EnemiesSprites/Guard33.png", "Media/EnemiesSprites/Guard34.png",
    "Media/EnemiesSprites/Guard35.png", "Media/EnemiesSprites/Guard36.png",
    "Media/EnemiesSprites/Guard37.png", "Media/EnemiesSprites/Guard38.png",
    "Media/EnemiesSprites/Guard39.png", "Media/EnemiesSprites/Guard40.png",
    "Media/EnemiesSprites/Guard41.png", "Media/EnemiesSprites/Guard42.png",
    "Media/EnemiesSprites/Guard43.png", "Media/EnemiesSprites/Guard44.png",
    "Media/EnemiesSprites/Guard45.png", "Media/EnemiesSprites/Guard46.png",
    "Media/EnemiesSprites/Guard47.png", "Media/EnemiesSprites/Guard48.png",
    "Media/EnemiesSprites/Guard49.png",
    };
    SpritesHandler EnemiesHandler;
    int angleEnemy = 0;
    int pos = 0;
public:
    Enemies();
    void defineSprite(Enemy_t &enemy, Vector &posPlayer, int &sprite);
    void defineFrame(Enemy_t &enemy);
    void setRenderer(SDL_Renderer* renderer);
    void setAngle(int angle);
    // void setPos(int anglePlayer);
    void setEnemy(int sprite);
    void recortar(int x, int y, int largo = LARGO, int alto = ALTO);
    void render(int x, int y, int largo = LARGO, int alto = ALTO);
    ~Enemies();
};

#endif 