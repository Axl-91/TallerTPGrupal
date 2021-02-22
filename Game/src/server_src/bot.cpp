#include "bot.h"

Bot::Bot(ProtectedQueue<MatchEvent_t> &aQueue,
        float x, float y, float ang, size_t ID,
        std::vector<std::vector<int>> &lvl):
    q(aQueue),
    lua(x,y,ang,ID, lvl)
{}

void Bot::setID(size_t anID){
    lua.setID(anID);
    ID = anID;
    // ID = anID;
}

void Bot::makeDecision(){
    MatchEvent_t event;
    event.playerTag = ID;
    lua.makeDecision(event.event);
    q.push(event);
}

void Bot::updateAPlayerInfo(Player_t &aPlayerInfo){
    lua.update(aPlayerInfo);
}

void Bot::setGameMap(std::vector<std::vector<int>> &aVector){
    lua.setGameMap(aVector);
}

void Bot::update(UpdateHandler &uHandler){
    Player_t playerInfo;
    uHandler.getPlayerChange(playerInfo);    

    // if(uHandler.mapChangeAvailable()){
    //     Map_change_t aMapChange;
    //     uHandler.getMapChange(aMapChange);
    //     AILua.sendMapUpdate(aMapChange);
    lua.update(playerInfo);  
}

