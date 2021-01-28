#ifndef CLIENTRECEIVER__T
#define CLIENTRECEIVER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "../common_src/protectedQueue.h"
#include "Game.h"

class ClientReceiver : public Thread {
public:
    ClientReceiver(Socket &socket, std::vector<std::vector<int>> &lvl2, Player_t &player, Map_change_t &mapC);
    ClientReceiver(ClientReceiver&& other);
    void operator()();
    virtual void run() override;
    void stop();
    void isAtMenu();
    void receiveMenuOption();
    void receiveGame();
    void receiveMap();
    void quitMatch();
    bool isInMatch();
    bool isDead();
    bool matchFinished();
    void receivePlayerInfo();
    void receiveMapChange();
    // void updatePlayer();
private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::atomic<bool> atMenus;
    std::vector<std::vector<int>>&lvl2;
    std::atomic<bool> inMatch;
    std::atomic<bool> matchEnded;
    Player_t &player;
    Map_change_t &mapChange;
};

#endif
