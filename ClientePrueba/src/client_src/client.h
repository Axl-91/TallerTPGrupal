#ifndef CLIENT__T
#define CLIENT__T

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <atomic>
#include <chrono>
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "../common_src/protectedEventQueue.h"
#include "clientReceiver.h"
#include "clientTransmitter.h"
#include "SDL_EventHandler.h"
#include "protectedUpdateQueue.h"
#include "Menu.h"
#include "TextHandler.h"
class Client{
public:
    Client(const char *host_name, const char *port);
    ~Client();
    void shutdown_writing();
    void connect(const char *host_name, const char *port);
    void run();
    void isAtMenu();
    void isInMatch();
private:
    std::stringstream petition;
    Socket s;
    std::atomic<bool> gameStarted;
    std::atomic<bool> connectedToMatch;
    ProtectedQueue<event_t> gameEventQ;
    // ProtectedQueue<menu_event_t> menuEventQ;
    // ProtectedQueue<menu_event_t> menuResponseQ;
    ClientTransmitter transmitter;
    ClientReceiver receiver;
    SDL_EventHandler eHandler;
    std::vector<std::vector<int>> lvl2;
    std::atomic<bool> is_running;
    // Player_t player;
    // Map_change_t mapChange;
    // Update_t anUpdate;
    ProtectedQueue<Update_t> gameUpdateQ;
    void runMenu(int &winLargo, int &winAlto);
    void runGame(int &winLargo, int &winAlto);
};

#endif
