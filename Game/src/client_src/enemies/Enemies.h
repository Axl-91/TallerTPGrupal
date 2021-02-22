#ifndef __TEXTURE_ENEMIES__
#define __TEXTURE_ENEMIES__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "EnemySpriteHandler.h"
#include "../../common_src/types.h"
#include "../../common_src/Vector.h"
#include "../SpritesHandler.h"
#include "ESHGuard.h"

#define LARGO 64
#define ALTO 64


//Clase que se ocupa del renderizado de enemigos
class Enemies{
private:
    enemy_type_t type;
    std::map<enemy_type_t, EnemySpriteHandler*> enemySpriteHandler;
public:
    Enemies();
    void setType(enemy_type_t t);
    void defineSprite(Enemy_t &enemy, Vector &posPlayer, int &sprite);
    void defineFrame(Enemy_t &enemy);
    void setRenderer(SDL_Renderer* renderer);
    void setEnemyRenderSprite(int sprite);
    void cutFromTexture(int &x, int &y, const int &largo = LARGO, const int &alto = ALTO);
    void render(int &x, int &y, const int &largo = LARGO, const int &alto = ALTO);
    ~Enemies();
};

#endif 