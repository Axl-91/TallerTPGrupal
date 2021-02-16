#include "EnemySpriteHandler.h"

EnemySpriteHandler::EnemySpriteHandler(std::vector<std::string> &enemiesSprites): 
spritesHandler(enemiesSprites){
    before = std::chrono::high_resolution_clock::now();
    movingFrameTimer = 0;
    shootingFrameTimer = 0;
    deadFrameTimer = 0;
    movingFrameTime = 100;
    shootingFrameTime = 100;
    deadFrameTime = 200;

}

void EnemySpriteHandler::setRenderer(SDL_Renderer* renderer){
    spritesHandler.setRenderer(renderer);
}


//usa trigonometria para definia la vista del enemigo
void EnemySpriteHandler::defineSprite(Enemy_t &enemy, Vector &posPlayer, int &sprite){
    Vector enemyPos(enemy.playerInfo.x, enemy.playerInfo.y);
    sprite=0;
    float auxAngle=enemyPos.getAngle(posPlayer);

    sprite += enemy.moving_frame * MOVEMENT_FRAME_OFFSET;

    if(auxAngle>=2*PI)
        auxAngle-=2*PI;
    if(auxAngle<0)
        auxAngle+=2*PI;

    float angleDif = (enemy.playerInfo.ang-auxAngle);

    if(angleDif>=2*PI)
        angleDif-=2*PI;
    if(angleDif<0)
        angleDif+=2*PI;

    angleDif=angleDif*180/PI;

    if (angleDif <= 22.5 && angleDif >= 0||angleDif <= 360 && angleDif > 337.5){
        sprite += 0;
            //si el enemigo esta de frente y esta disparando, se ve la animacion de disparo
            if(enemy.playerInfo.shootingState!=SHOOTING_STATE_QUIET || enemy.shooting_frame!=0){
                sprite = enemy.shooting_frame + shootingFramesOffset;
                return;
            }

    } else if (angleDif > 22.5 && angleDif <= 67.5){
        sprite += 1;
    } else if (angleDif > 67.5 && angleDif <= 112.5){
        sprite += 2;
    } else if (angleDif > 112.5 && angleDif <= 157.5){
        sprite += 3;
    } else if (angleDif > 157.5 && angleDif <= 202.5){
        sprite += 4;
    } else if (angleDif > 202.5 && angleDif <= 247.5){
        sprite += 5;
    } else if (angleDif > 247.5 && angleDif <= 292.5){
        sprite += 6;
    } else if (angleDif > 292.5  && angleDif <= 337.5){
        sprite += 7;
    }

}


void EnemySpriteHandler::defineFrame(Enemy_t &enemy){
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);

    defineMovingFrame(enemy);
    defineShootingFrame(enemy);
    defineDeadFrame(enemy);
    before = now;
}

void EnemySpriteHandler::defineMovingFrame(Enemy_t &enemy){
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
    movingFrameTimer += waited.count();
    
    if(enemy.playerInfo.moving==false || enemy.moving_frame>=movementFrames-1)
        enemy.moving_frame=0;
    else if(movingFrameTimer >= movingFrameTime){
        enemy.moving_frame++;
        movingFrameTimer = 0;
    }
}

void EnemySpriteHandler::defineShootingFrame(Enemy_t &enemy){
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
    shootingFrameTimer += waited.count();
    
    if(enemy.playerInfo.shootingState==SHOOTING_STATE_QUIET && enemy.shooting_frame!=1)
        enemy.shooting_frame = 0;    
    else if(shootingFrameTimer >= shootingFrameTime){
        if(enemy.shooting_frame>=shootingFrames-1)
            enemy.shooting_frame = 1;
        else 
            enemy.shooting_frame++;
        shootingFrameTimer = 0;
    }
}

void EnemySpriteHandler::defineDeadFrame(Enemy_t &enemy){
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
    deadFrameTimer += waited.count();

    if(enemy.dead==false || enemy.dead_frame>=deadFrames-1)
        enemy.dead_frame=0;
    else if(deadFrameTimer >= deadFrameTime){
        enemy.dead_frame++;
        deadFrameTimer = 0;
    }
    
}

void EnemySpriteHandler::setEnemyRenderSprite(int sprite){
    frame=sprite;
}

void EnemySpriteHandler::cutFromTexture(int x, int y, int largo, int alto){
    spritesHandler.setSrc(x, y, largo,alto);
}

void EnemySpriteHandler::render(int x, int y, int largo, int alto){
    spritesHandler.render(x, y, largo, alto, frame);
}

EnemySpriteHandler::~EnemySpriteHandler(){}
