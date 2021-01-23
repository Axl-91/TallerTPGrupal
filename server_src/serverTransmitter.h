#ifndef SERVERTRANSMITTER__T
#define SERVERTRANSMITTER__T

#include <vector>
#include <sstream>
#include "../common_src/socket.h"

class ServerTransmitter {
public:
    ServerTransmitter(Socket &socket);
    ServerTransmitter(ServerTransmitter&& other);
    void send(std::stringstream &game);
private:
    Socket &socket;
};

#endif
