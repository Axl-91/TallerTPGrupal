#ifndef UPDATEHANDLER__T
#define UPDATEHANDLER__T

#include <vector>
#include "../common_src/types.h"
#include "serverPlayer.h"
class UpdateHandler{
private:
    Player_t player;
    Map_change_t mapChange;
    bool mapChanged;
    bool playerChanged;
public:
    // sendUpdate();
    void updateMap(int xAux, int yAux, int value);
    void updatePlayerPosition(ServerPlayer &player);
    bool mapChangeAvailable();
    bool playerChangeAvailable();
    void getMapChange(Map_change_t &aMapChange);
    void getPlayerChange(Player_t &p);
    void updated();
};

#endif
