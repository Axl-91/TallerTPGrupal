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
    ClientReceiver(Socket &socket, 
                std::vector<std::vector<int>> &m, 
                ProtectedQueue<Update_t> &uQ,
                ProtectedQueue<menu_event_t> &mQ);
    void operator()();
    virtual void run() override;
    void stop();
    void quitMatch();
    bool isInMatch();
    bool isDead();
    bool matchFinished();
    void receiveString(std::string &aString);
    void receiveMatchList();

private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::vector<std::vector<int>>&map;
    std::atomic<bool> inMatch;
    std::atomic<bool> matchEnded;
    ProtectedQueue<Update_t> &uQ;
    ProtectedQueue<menu_event_t> &menuResponseQ;
    void receivePlayerInfo(Update_t &anUpdate);
    void receiveMapChange(Update_t &anUpdate);
    void receiveGame();
    void receiveMap();
};

#endif
