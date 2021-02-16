#include "ESHMutant.h"



std::vector<std::string> enemieSpritesMutant = {
    "Media/EnemiesSprites/Mutant01.png", "Media/EnemiesSprites/Mutant02.png",
    "Media/EnemiesSprites/Mutant03.png", "Media/EnemiesSprites/Mutant04.png",
    "Media/EnemiesSprites/Mutant05.png", "Media/EnemiesSprites/Mutant06.png",
    "Media/EnemiesSprites/Mutant07.png", "Media/EnemiesSprites/Mutant08.png",
    "Media/EnemiesSprites/Mutant09.png", "Media/EnemiesSprites/Mutant10.png",
    "Media/EnemiesSprites/Mutant11.png", "Media/EnemiesSprites/Mutant12.png",
    "Media/EnemiesSprites/Mutant13.png", "Media/EnemiesSprites/Mutant14.png",
    "Media/EnemiesSprites/Mutant15.png", "Media/EnemiesSprites/Mutant16.png",
    "Media/EnemiesSprites/Mutant17.png", "Media/EnemiesSprites/Mutant18.png",
    "Media/EnemiesSprites/Mutant19.png", "Media/EnemiesSprites/Mutant20.png",
    "Media/EnemiesSprites/Mutant21.png", "Media/EnemiesSprites/Mutant22.png",
    "Media/EnemiesSprites/Mutant23.png", "Media/EnemiesSprites/Mutant24.png",
    "Media/EnemiesSprites/Mutant25.png", "Media/EnemiesSprites/Mutant26.png",
    "Media/EnemiesSprites/Mutant27.png", "Media/EnemiesSprites/Mutant28.png",
    "Media/EnemiesSprites/Mutant29.png", "Media/EnemiesSprites/Mutant30.png",
    "Media/EnemiesSprites/Mutant31.png", "Media/EnemiesSprites/Mutant32.png",
    "Media/EnemiesSprites/Mutant33.png", "Media/EnemiesSprites/Mutant34.png",
    "Media/EnemiesSprites/Mutant35.png", "Media/EnemiesSprites/Mutant36.png",
    "Media/EnemiesSprites/Mutant37.png", "Media/EnemiesSprites/Mutant38.png",
    "Media/EnemiesSprites/Mutant39.png", "Media/EnemiesSprites/Mutant40.png",
    "Media/EnemiesSprites/Mutant41.png", "Media/EnemiesSprites/Mutant42.png",
    "Media/EnemiesSprites/Mutant43.png", "Media/EnemiesSprites/Mutant44.png",
    "Media/EnemiesSprites/Mutant45.png", "Media/EnemiesSprites/Mutant46.png",
    "Media/EnemiesSprites/Mutant47.png", "Media/EnemiesSprites/Mutant48.png",
    "Media/EnemiesSprites/Mutant49.png", "Media/EnemiesSprites/Mutant50.png"
    };

ESHMutant::ESHMutant():EnemySpriteHandler(enemieSpritesMutant){
    type = MUTANT;
    movementFrames = MUTANT_MOVEMENT_FRAMES;
    shootingFrames = MUTANT_SHOOT_FRAMES;
    deadFrames = MUTANT_DEAD_FRAMES;
    shootingFramesOffset = MUTANT_SHOOT_FRAMES_OFFSET;
    deadFramesOffset = MUTANT_DEAD_FRAMES_OFFSET;

}
ESHMutant::~ESHMutant(){}