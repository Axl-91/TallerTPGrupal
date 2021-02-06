#ifndef CLIENTRECEIVER__T
#define CLIENTRECEIVER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/thread.h"
#include "../common_src/types.h"
#include "../common_src/socket.h"
#include "../common_src/protectedQueue.h"
#include "protectedUpdateQueue.h"
#include "Game.h"

class ClientReceiver : public Thread {
public:
    ClientReceiver(Socket &socket, std::vector<std::vector<int>> &m, ProtectedUpdateQueue &uQ);
    void operator()();
    virtual void run() override;
    void stop();
    void quitMatch();
    bool isInMatch();
    bool isDead();
    bool matchFinished();

private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::vector<std::vector<int>>&map;
    std::atomic<bool> inMatch;
    std::atomic<bool> matchEnded;
    ProtectedUpdateQueue &uQ;
    void receivePlayerInfo(Update_t &anUpdate);
    void receiveMapChange(Update_t &anUpdate);
    void receiveGame();
    void receiveMap();
};

#endif
