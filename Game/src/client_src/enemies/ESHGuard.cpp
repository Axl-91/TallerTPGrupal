#include "ESHGuard.h"



std::vector<std::string> enemieSpritesGuard = {
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

ESHGuard::ESHGuard():EnemySpriteHandler(enemieSpritesGuard){
    movementFrames = GUARD_MOVEMENT_FRAMES;
    shootingFrames = GUARD_SHOOT_FRAMES;
    deadFrames = GUARD_DEAD_FRAMES;
    shootingFramesOffset = GUARD_SHOOT_FRAMES_OFFSET;
    deadFramesOffset =GUARD_DEAD_FRAMES_OFFSET;

    type = GUARD;
}
ESHGuard::~ESHGuard(){}


