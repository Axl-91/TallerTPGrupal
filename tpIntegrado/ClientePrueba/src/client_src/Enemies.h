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

// typedef struct{
//     Vector pos;
//     float ang;
//     int type;
// }Enemy_t;

class Enemies{
private:
    std::vector<std::string> EnemiesSprites = {
    // "Media/EnemiesSprites/asd.png", "Media/EnemiesSprites/dsadGuard02.png",
    // "Media/EnemiesSprites/Guarddawd03.png", "Media/EnemiesSprites/Guarddda04.png",
    // "Media/EnemiesSprites/Guardawdd05.png", "Media/EnemiesSprites/Guardd06.png",
    // "Media/EnemiesSprites/Guardawdad07.png", "Media/EnemiesSprites/Guaddrd08.png",
    "Media/EnemiesSprites/Guard01.png", "Media/EnemiesSprites/Guard02.png",
    "Media/EnemiesSprites/Guard03.png", "Media/EnemiesSprites/Guard04.png",
    "Media/EnemiesSprites/Guard05.png", "Media/EnemiesSprites/Guard06.png",
    "Media/EnemiesSprites/Guard07.png", "Media/EnemiesSprites/Guard08.png",
    };
    SpritesHandler EnemiesHandler;
    int angleEnemy = 0;
    //angleEnemy con angulo en grados
    int pos = 0;
public:
    Enemies();
    void defineSprite(Player_t enemy, Vector &posPlayer, int &sprite);

    void setRenderer(SDL_Renderer* renderer);
    void setAngle(int angle);
    // void setPos(int anglePlayer);
    void setEnemy(int sprite);
    void recortar(int x, int y, int largo = LARGO, int alto = ALTO);
    void render(int x, int y, int largo = LARGO, int alto = ALTO);
    ~Enemies();
};

#endif 

// #ifndef __TEXTURE_ENEMIES__
// #define __TEXTURE_ENEMIES__

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// // #include "Vector.h"
// #include "SDLHandler.h"
// #include "SpritesHandler.h"
// #include "../common_src/Vector.h"

// #define LARGO 64
// #define ALTO 64

// typedef struct{
//     Vector pos;
//     float ang;
//     int type;
// }Enemy_t;


// class Enemies{
// private:
//     std::vector<std::string> EnemiesSprites = {
//     "Media/EnemiesSprites/Guard01.png", "Media/EnemiesSprites/Guard02.png",
//     "Media/EnemiesSprites/Guard03.png", "Media/EnemiesSprites/Guard04.png",
//     "Media/EnemiesSprites/Guard05.png", "Media/EnemiesSprites/Guard06.png",
//     "Media/EnemiesSprites/Guard07.png", "Media/EnemiesSprites/Guard08.png",
//     };
//     // int sprite;
//     SpritesHandler EnemiesHandler;
//     int angleEnemy = 0;
//     //angleEnemy con angulo en grados
//     int pos = 0;
// public:
//     Enemies();
//     void defineSprite(Enemy_t enemy, Vector &posPlayer, int &sprite);

//     void setRenderer(SDL_Renderer* renderer);
//     void setAngle(int angle);
//     // void setPos(int anglePlayer);
//     void setEnemy(int sprite);
//     void recortar(int x, int y, int largo = LARGO, int alto = ALTO);
//     void render(int x, int y, int largo = LARGO, int alto = ALTO);
//     ~Enemies();
// };

// #endif