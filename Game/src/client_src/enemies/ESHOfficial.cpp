#include "ESHOfficial.h"



std::vector<std::string> enemieSpritesOfficial = {
    "Media/EnemiesSprites/oficer01.png", "Media/EnemiesSprites/oficer02.png",
    "Media/EnemiesSprites/oficer03.png", "Media/EnemiesSprites/oficer04.png",
    "Media/EnemiesSprites/oficer05.png", "Media/EnemiesSprites/oficer06.png",
    "Media/EnemiesSprites/oficer07.png", "Media/EnemiesSprites/oficer08.png",
    "Media/EnemiesSprites/oficer09.png", "Media/EnemiesSprites/oficer10.png",
    "Media/EnemiesSprites/oficer11.png", "Media/EnemiesSprites/oficer12.png",
    "Media/EnemiesSprites/oficer13.png", "Media/EnemiesSprites/oficer14.png",
    "Media/EnemiesSprites/oficer15.png", "Media/EnemiesSprites/oficer16.png",
    "Media/EnemiesSprites/oficer17.png", "Media/EnemiesSprites/oficer18.png",
    "Media/EnemiesSprites/oficer19.png", "Media/EnemiesSprites/oficer20.png",
    "Media/EnemiesSprites/oficer21.png", "Media/EnemiesSprites/oficer22.png",
    "Media/EnemiesSprites/oficer23.png", "Media/EnemiesSprites/oficer24.png",
    "Media/EnemiesSprites/oficer25.png", "Media/EnemiesSprites/oficer26.png",
    "Media/EnemiesSprites/oficer27.png", "Media/EnemiesSprites/oficer28.png",
    "Media/EnemiesSprites/oficer29.png", "Media/EnemiesSprites/oficer30.png",
    "Media/EnemiesSprites/oficer31.png", "Media/EnemiesSprites/oficer32.png",
    "Media/EnemiesSprites/oficer33.png", "Media/EnemiesSprites/oficer34.png",
    "Media/EnemiesSprites/oficer35.png", "Media/EnemiesSprites/oficer36.png",
    "Media/EnemiesSprites/oficer37.png", "Media/EnemiesSprites/oficer38.png",
    "Media/EnemiesSprites/oficer39.png", "Media/EnemiesSprites/oficer40.png",
    "Media/EnemiesSprites/oficer41.png", "Media/EnemiesSprites/oficer42.png",
    "Media/EnemiesSprites/oficer43.png", "Media/EnemiesSprites/oficer44.png",
    "Media/EnemiesSprites/oficer45.png", "Media/EnemiesSprites/oficer46.png",
    "Media/EnemiesSprites/oficer47.png", "Media/EnemiesSprites/oficer48.png",
    "Media/EnemiesSprites/oficer49.png", "Media/EnemiesSprites/oficer50.png"
    };

ESHOfficial::ESHOfficial():EnemySpriteHandler(enemieSpritesOfficial){
    type = OFFICIAL;
    movementFrames = OFFICIAL_MOVEMENT_FRAMES;
    shootingFrames = OFFICIAL_SHOOT_FRAMES;
    deadFrames = OFFICIAL_DEAD_FRAMES;
    shootingFramesOffset = OFFICIAL_SHOOT_FRAMES_OFFSET;
    deadFramesOffset = OFFICIAL_DEAD_FRAMES_OFFSET;

}
ESHOfficial::~ESHOfficial(){}