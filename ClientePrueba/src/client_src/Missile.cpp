#include "Missile.h"


std::vector<std::string> missileSprites = {
    "Media/Missile/MISSILE01.png", "Media/Missile/MISSILE02.png",
    "Media/Missile/MISSILE03.png", "Media/Missile/MISSILE04.png",
    "Media/Missile/MISSILE05.png", "Media/Missile/MISSILE06.png",
    "Media/Missile/MISSILE07.png", "Media/Missile/MISSILE08.png",
    "Media/Missile/MISSILE09.png", "Media/Missile/MISSILE10.png",
    "Media/Missile/MISSILE11.png"
};


Missile::Missile(): 
spritesHandler(missileSprites){
    before = std::chrono::high_resolution_clock::now();
    frame = 0;
//    explodeFrameTimer = 0;
    explodeFrames = 3;
    explodeFramesOffset = 8;
    explodeFrameTime = 200;
}

void Missile::setRenderer(SDL_Renderer* renderer){
    spritesHandler.setRenderer(renderer);
}


//usa trigonometria para definir la vista del misil
void Missile::defineSprite(Render_missile_t &missile, Vector &posPlayer, int &sprite){
    Vector missilePos(missile.info.x, missile.info.y);
    defineFrame(missile);
    sprite=0;
    float auxAngle=missilePos.getAngle(posPlayer);

    if(missile.info.exploding==true){
        sprite = explodeFramesOffset + missile.explode_frame+600;
        return;
    }

    if(auxAngle>=2*PI)
        auxAngle-=2*PI;
    if(auxAngle<0)
        auxAngle+=2*PI;

    float angleDif = (missile.info.ang-auxAngle);

    if(angleDif >= 2*PI)
        angleDif -= 2*PI;
    if(angleDif < 0)
        angleDif += 2*PI;

    angleDif = angleDif * 180/PI;

    if (angleDif <= 22.5 && angleDif >= 0||angleDif <= 360 && angleDif > 337.5){
        sprite += 0;
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

    sprite+=600;

}


void Missile::defineFrame(Render_missile_t &missile){
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);

    defineExplodeFrame(missile);
    before = now;
}

void Missile::defineExplodeFrame(Render_missile_t &missile){
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
    missile.explodeFrameTimer += waited.count();
    if(missile.info.exploding == false){
        missile.explode_frame = 0;
        missile.explodeFrameTimer = 0;

    }else if(missile.explode_frame >= explodeFrames-1 
    && missile.explodeFrameTimer >= explodeFrameTime){
        missile.exploded = true;
    }else if(missile.explodeFrameTimer >= explodeFrameTime){
        missile.explode_frame++;
        missile.explodeFrameTimer = 0;
    }
}

void Missile::setEnemyRenderSprite(int sprite){
    frame=sprite-600;
}

void Missile::cutFromTexture(int x, int y, int largo, int alto){
    spritesHandler.setSrc(x, y, largo,alto);
}

void Missile::render(int x, int y, int largo, int alto){
    spritesHandler.render(x, y, largo, alto, frame);
}

Missile::~Missile(){}
