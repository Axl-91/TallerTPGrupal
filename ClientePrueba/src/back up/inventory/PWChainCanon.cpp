#include "PWChainCanon.h"

std::vector<std::string> PWChainCanonSprites={
    "Media/WeaponSprites/PWChainCanon0.png",
    "Media/WeaponSprites/PWChainCanon1.png",
    "Media/WeaponSprites/PWChainCanon2.png",
    "Media/WeaponSprites/PWChainCanon3.png",
    "Media/WeaponSprites/PWChainCanon4.png"
};


PWChainCanon::PWChainCanon():
PlayerWeapon(PWChainCanonSprites){
    type=CHAIN_CANON;
}

PWChainCanon::~PWChainCanon(){}