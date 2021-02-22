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

// Recibe los mensajes del servidor. Durante etapa de menu encola respuestas de menu en cola de respuestas. 
// Durante partida encola updates del juego en una cola de actualizaciones del juego.
class ClientReceiver : public Thread {
public:   
    ClientReceiver(Socket &socket, 
                std::vector<std::vector<int>> &m, 
                ProtectedQueue<Update_t> &uQ);
    void operator()();
    virtual void run() override;
    void stop();
    void quitMatch();
    bool isInMatch();
    bool isDead();
    bool matchFinished();
    void receiveString(std::string &aString);
    // void receiveMatchList();
    // void receiveMapList();

private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::vector<std::vector<int>>&map;
    std::atomic<bool> inMatch;
    std::atomic<bool> matchEnded;
    ProtectedQueue<Update_t> &uQ;

    // ProtectedQueue<menu_event_t> &menuResponseQ;
    void receivePlayerInfo(Update_t &anUpdate);
    void receiveMapChange(Update_t &anUpdate);
    void receiveGame();
    void receiveMap();
    void receiveMissileInfo(Update_t &anUpdate);

};

#endif
