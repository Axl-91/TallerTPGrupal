#include "ESHHound.h"



std::vector<std::string> enemieSpritesHound = {
    "Media/EnemiesSprites/Dog01.png", "Media/EnemiesSprites/Dog02.png",
    "Media/EnemiesSprites/Dog03.png", "Media/EnemiesSprites/Dog04.png",
    "Media/EnemiesSprites/Dog05.png", "Media/EnemiesSprites/Dog06.png",
    "Media/EnemiesSprites/Dog07.png", "Media/EnemiesSprites/Dog08.png",
    "Media/EnemiesSprites/Dog09.png", "Media/EnemiesSprites/Dog10.png",
    "Media/EnemiesSprites/Dog11.png", "Media/EnemiesSprites/Dog12.png",
    "Media/EnemiesSprites/Dog13.png", "Media/EnemiesSprites/Dog14.png",
    "Media/EnemiesSprites/Dog15.png", "Media/EnemiesSprites/Dog16.png",
    "Media/EnemiesSprites/Dog17.png", "Media/EnemiesSprites/Dog18.png",
    "Media/EnemiesSprites/Dog19.png", "Media/EnemiesSprites/Dog20.png",
    "Media/EnemiesSprites/Dog21.png", "Media/EnemiesSprites/Dog22.png",
    "Media/EnemiesSprites/Dog23.png", "Media/EnemiesSprites/Dog24.png",
    "Media/EnemiesSprites/Dog25.png", "Media/EnemiesSprites/Dog26.png",
    "Media/EnemiesSprites/Dog27.png", "Media/EnemiesSprites/Dog28.png",
    "Media/EnemiesSprites/Dog29.png", "Media/EnemiesSprites/Dog30.png",
    "Media/EnemiesSprites/Dog31.png", "Media/EnemiesSprites/Dog32.png",
    "Media/EnemiesSprites/Dog33.png", "Media/EnemiesSprites/Dog34.png",
    "Media/EnemiesSprites/Dog35.png", "Media/EnemiesSprites/Dog36.png",
    "Media/EnemiesSprites/Dog37.png", "Media/EnemiesSprites/Dog38.png",
    "Media/EnemiesSprites/Dog39.png"
    };

ESHHound::ESHHound():EnemySpriteHandler(enemieSpritesHound){
    type = HOUND;
    movementFrames = HOUND_MOVEMENT_FRAMES;
    shootingFrames = HOUND_SHOOT_FRAMES;
    deadFrames = HOUND_DEAD_FRAMES;
    shootingFramesOffset = HOUND_SHOOT_FRAMES_OFFSET;
    deadFramesOffset =HOUND_DEAD_FRAMES_OFFSET;

}
ESHHound::~ESHHound(){}