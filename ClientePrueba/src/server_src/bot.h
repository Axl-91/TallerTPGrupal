#ifndef BOT__H
#define BOT__H

#include "../common_src/types.h"
#include "../common_src/protectedEventQueue.h"

class Bot{
private:
    Player_t playerInfo;
    
public:
    Bot(float x, float y, float ang, size_t ID);
    void pichula();
    void update(Update_t &anUpdate);
    void makeDecision();
};

#endif
