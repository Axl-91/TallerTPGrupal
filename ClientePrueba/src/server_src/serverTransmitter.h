#ifndef SERVERTRANSMITTER__T
#define SERVERTRANSMITTER__T

#include <vector>
#include <sstream>
#include "../common_src/socket.h"
#include "../common_src/types.h"
#include <mutex>

class ServerTransmitter {
public:
    ServerTransmitter(Socket &socket);
    ServerTransmitter(ServerTransmitter&& other);
    void sendTag(update_tag_t &aTag);
    void sendMap(std::vector<std::vector<int>> &lvl1);
    void sendPlayer(Player_t &player);   
    // void sendUpdate(Update_t &anUpdate);   
    void sendMapUpdate(Map_change_t &aMapChange);
    void sendPlayerID(size_t &ID);
    void sendString(std::string &aString);

private:
    std::mutex m;
    Socket &socket;
};

#endif
