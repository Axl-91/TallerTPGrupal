#ifndef SERVERRECEIVER__T
#define SERVERRECEIVER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/socket.h"
#include "protectedQueue.h"

class ServerReceiver{
public:
    ServerReceiver(Socket &socket);
    ServerReceiver(ServerReceiver&& other);
    void readInput(std::string &input);
    void stop();
private:
    Socket &socket;
};

#endif
