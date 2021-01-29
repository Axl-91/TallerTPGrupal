#ifndef CLIENT__T
#define CLIENT__T

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <atomic>
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "../common_src/protectedEventQueue.h"
#include "clientReceiver.h"
#include "clientTransmitter.h"
#include "SDL_EventHandler.h"
class Client{
public:
    Client(const char *host_name, const char *port);
    ~Client();
    void read_petition();
    void shutdown_writing();
    void connect(const char *host_name, const char *port);
    void run();
    void isAtMenu();
    void isInMatch();
private:
    std::stringstream petition;
    Socket s;
    std::atomic<bool> atMenus;
    std::atomic<bool> connectedToMatch;
    ProtectedEventQueue q;
    ClientTransmitter transmitter;
    ClientReceiver receiver;
    SDL_EventHandler eHandler;
    std::vector<std::vector<int>> lvl2;
    std::atomic<bool> is_running;
    Player_t player;
    Map_change_t mapChange;
};

#endif
