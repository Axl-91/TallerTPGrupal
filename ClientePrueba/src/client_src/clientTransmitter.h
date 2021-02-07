#ifndef CLIENTTRANSMITTER__T
#define CLIENTTRANSMITTER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "../common_src/protectedQueue.h"
#include "../common_src/protectedEventQueue.h"

class ClientTransmitter : public Thread {
public:
    ClientTransmitter(Socket &socket, ProtectedQueue<event_t> &gQ, ProtectedQueue<menu_event_t> &mQ);
    void operator()();
    bool isRunning();
    void sendGameEvent();
    void sendMenuEvent();
    virtual void run() override;
    void isAtMenu();
    void isInMatch();
    void stop();
private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::atomic<bool> atMenus;
    ProtectedQueue<event_t> &gameEventQ;
    ProtectedQueue<menu_event_t> &menuEventQ;
};

#endif