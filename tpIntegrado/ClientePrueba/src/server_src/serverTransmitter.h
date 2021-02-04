#ifndef SERVERTRANSMITTER__T
#define SERVERTRANSMITTER__T

#include <vector>
#include <sstream>
#include "../common_src/socket.h"
#include "../common_src/types.h"

class ServerTransmitter {
public:
    ServerTransmitter(Socket &socket);
    ServerTransmitter(ServerTransmitter&& other);
    void send(std::stringstream &game);
    void sendMap(std::vector<std::vector<int>> &lvl1);
    void sendPlayer(Player_t player);   
    void sendMapUpdate(Map_change_t &aMapChange);
    void sendPlayerID(size_t &ID);

private:
    Socket &socket;
};

#endif
