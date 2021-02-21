#include "SPWRocketLauncher.h"


SPWRocketLauncher::SPWRocketLauncher(){
    type = ROCKET_LAUNCHER;
    before = std::chrono::high_resolution_clock::now();
    damage = ROCKET_LAUNCHER_DAMAGE;
    usedBullets = ROCKET_LAUNCHER_USED_BULLETS;
}

SPWRocketLauncher::~SPWRocketLauncher(){}


float SPWRocketLauncher::shoot(shooting_state_t &shootingState, bool &shootMissile){
    shootMissile = false;

    if(shooting == false){
        shootingState = SHOOTING_STATE_QUIET;
        return 0;
    }
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
    if(waited.count()<ROCKET_LAUNCHER_WAIT_TIME){
//        shootingState = SHOOTING_STATE_QUIET;
        return 0;
    }

    before = now;
    shooting = false;
    shootMissile = true;
    return damage;
}
