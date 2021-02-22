#ifndef SERVERRECEIVER__T
#define SERVERRECEIVER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/socket.h"
#include "../common_src/types.h"
#include "../common_src/protectedQueue.h"


class ServerReceiver{
public:
    ServerReceiver(Socket &socket);
    ServerReceiver(ServerReceiver&& other);
    // void readInput(std::string &input);
    void readGameEvent(event_t &event);
    void readMenuEvent(menu_event_t &menuEvent);
    void stop();
    bool finished();
private:
    Socket &socket;
    std::atomic<bool> is_running;
};

#endif
