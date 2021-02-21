#include "SPWKnife.h"

SPWKnife::SPWKnife(){
    type=KNIFE;
    damage=KNIFE_DAMAGE;
    before = std::chrono::high_resolution_clock::now();
    usedBullets = KNIFE_USED_BULLETS;
}
SPWKnife::~SPWKnife(){}

float SPWKnife::shoot(shooting_state_t &shootingState, bool &shootMissile){
    shootMissile = false;
    if(shooting == false){
        shootingState = SHOOTING_STATE_QUIET;
        return 0;
    }

    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
    if(waited.count()<KNIFE_WAIT_TIME){
//        shootingState = SHOOTING_STATE_WAIT;
        shooting=false;
        return 0;
    }

    before=now;
    shooting=false;
    return damage;
}
