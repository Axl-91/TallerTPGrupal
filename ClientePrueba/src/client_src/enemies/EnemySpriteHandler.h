#ifndef _ENEMY_SPRITE_HANDLER_H_
#define _ENEMY_SPRITE_HANDLER_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../SpritesHandler.h"
#include "../../common_src/types.h"
#include "../../common_src/Vector.h"
#include <chrono>


#define MOVEMENT_FRAME_OFFSET 8

#define HOUND_MOVEMENT_FRAMES 4
#define GUARD_MOVEMENT_FRAMES 5
#define OFFICIAL_MOVEMENT_FRAMES 5
#define SS_MOVEMENT_FRAMES 5
#define MUTANT_MOVEMENT_FRAMES 5


#define HOUND_SHOOT_FRAMES_OFFSET 36
#define GUARD_SHOOT_FRAMES_OFFSET 46
#define OFFICIAL_SHOOT_FRAMES_OFFSET 47
#define SS_SHOOT_FRAMES_OFFSET 46
#define MUTANT_SHOOT_FRAMES_OFFSET 47


#define HOUND_SHOOT_FRAMES 3
#define GUARD_SHOOT_FRAMES 3
#define OFFICIAL_SHOOT_FRAMES 3
#define SS_SHOOT_FRAMES 3
#define MUTANT_SHOOT_FRAMES 3


#define HOUND_DEAD_FRAMES_OFFSET 32
#define GUARD_DEAD_FRAMES_OFFSET 40
#define OFFICIAL_DEAD_FRAMES_OFFSET 40
#define SS_DEAD_FRAMES_OFFSET 40
#define MUTANT_DEAD_FRAMES_OFFSET 40


#define HOUND_DEAD_FRAMES 4
#define GUARD_DEAD_FRAMES 5
#define OFFICIAL_DEAD_FRAMES 6
#define SS_DEAD_FRAMES 5
#define MUTANT_DEAD_FRAMES 6


class EnemySpriteHandler{
    SpritesHandler spritesHandler;
    int angleEnemy = 0;
    int frame = 0;
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;

    float movingFrameTimer;
    float shootingFrameTimer;
    float deadFrameTimer;

protected:
    enemy_type_t type;
    int movementFrames;
    int shootingFrames;
    int shootingFramesOffset;
    int deadFrames;
    int deadFramesOffset;

    float movingFrameTime;
    float shootingFrameTime;
    float deadFrameTime;

public:
    EnemySpriteHandler(std::vector<std::string> &EnemiesSprites);
    ~EnemySpriteHandler();

    void defineSprite(Enemy_t &enemy, Vector &posPlayer, int &sprite);
    void defineFrame(Enemy_t &enemy);
    void setRenderer(SDL_Renderer* renderer);
    void setEnemyRenderSprite(int sprite);
    void cutFromTexture(int x, int y, int largo, int alto);
    void render(int x, int y, int largo, int alto);

private:
    void defineDeadFrame(Enemy_t &enemy);
    void defineShootingFrame(Enemy_t &enemy);
    void defineMovingFrame(Enemy_t &enemy);

};




#endif
