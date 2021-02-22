#include "ESHSS.h"



std::vector<std::string> enemieSpritesSS = {
    "Media/EnemiesSprites/ss01.png", "Media/EnemiesSprites/ss02.png",
    "Media/EnemiesSprites/ss03.png", "Media/EnemiesSprites/ss04.png",
    "Media/EnemiesSprites/ss05.png", "Media/EnemiesSprites/ss06.png",
    "Media/EnemiesSprites/ss07.png", "Media/EnemiesSprites/ss08.png",
    "Media/EnemiesSprites/ss09.png", "Media/EnemiesSprites/ss10.png",
    "Media/EnemiesSprites/ss11.png", "Media/EnemiesSprites/ss12.png",
    "Media/EnemiesSprites/ss13.png", "Media/EnemiesSprites/ss14.png",
    "Media/EnemiesSprites/ss15.png", "Media/EnemiesSprites/ss16.png",
    "Media/EnemiesSprites/ss17.png", "Media/EnemiesSprites/ss18.png",
    "Media/EnemiesSprites/ss19.png", "Media/EnemiesSprites/ss20.png",
    "Media/EnemiesSprites/ss21.png", "Media/EnemiesSprites/ss22.png",
    "Media/EnemiesSprites/ss23.png", "Media/EnemiesSprites/ss24.png",
    "Media/EnemiesSprites/ss25.png", "Media/EnemiesSprites/ss26.png",
    "Media/EnemiesSprites/ss27.png", "Media/EnemiesSprites/ss28.png",
    "Media/EnemiesSprites/ss29.png", "Media/EnemiesSprites/ss30.png",
    "Media/EnemiesSprites/ss31.png", "Media/EnemiesSprites/ss32.png",
    "Media/EnemiesSprites/ss33.png", "Media/EnemiesSprites/ss34.png",
    "Media/EnemiesSprites/ss35.png", "Media/EnemiesSprites/ss36.png",
    "Media/EnemiesSprites/ss37.png", "Media/EnemiesSprites/ss38.png",
    "Media/EnemiesSprites/ss39.png", "Media/EnemiesSprites/ss40.png",
    "Media/EnemiesSprites/ss41.png", "Media/EnemiesSprites/ss42.png",
    "Media/EnemiesSprites/ss43.png", "Media/EnemiesSprites/ss44.png",
    "Media/EnemiesSprites/ss45.png", "Media/EnemiesSprites/ss46.png",
    "Media/EnemiesSprites/ss47.png", "Media/EnemiesSprites/ss48.png",
    "Media/EnemiesSprites/ss49.png"
    };

ESHSS::ESHSS():EnemySpriteHandler(enemieSpritesSS){
    type = SS;
    movementFrames = SS_MOVEMENT_FRAMES;
    shootingFrames = SS_SHOOT_FRAMES;
    deadFrames = SS_DEAD_FRAMES;
    shootingFramesOffset = SS_SHOOT_FRAMES_OFFSET;
    deadFramesOffset = SS_DEAD_FRAMES_OFFSET;
}

ESHSS::~ESHSS(){}
