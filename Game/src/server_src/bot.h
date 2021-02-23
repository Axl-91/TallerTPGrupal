#ifndef BOT__H
#define BOT__H

#include "../common_src/types.h"
#include "../common_src/protectedQueue.h"
#include "AILua.h"
#include "updateHandler.h"

class Bot{
private:
    size_t ID;
    ProtectedQueue<MatchEvent_t> &q;
    AILua lua;
public:
    Bot(ProtectedQueue<MatchEvent_t> &aQueue,
        float x, float y, float ang, size_t ID,
        std::vector<std::vector<int>> &lvl);
    void pichula();
    void makeDecision();
    void setID(size_t anID);
    void update(UpdateHandler &uHandler);
    void updateAPlayerInfo(Player_t &aPlayerInfo);
};

#endif
