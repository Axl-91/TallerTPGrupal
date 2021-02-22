#ifndef CLIENTTRANSMITTER__T
#define CLIENTTRANSMITTER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "../common_src/protectedQueue.h"
#include "../common_src/protectedEventQueue.h"


// Recibe una cola de eventos de menu y una cola de eventos de la partida. 
// Al ver que una de las colas no está vacía, envía el evento que encuentre al servidor.
class ClientTransmitter : public Thread {
public:
    ClientTransmitter(Socket &socket, 
            ProtectedQueue<event_t> &gQ);
    void operator()();
    bool isRunning();
    void sendGameEvent();
    void sendMenuEvent(menu_event_t &event);
    virtual void run() override;
    void isAtMenu();
    void isInMatch();
    void stop();
private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::atomic<bool> atMenus;
    ProtectedQueue<event_t> &gameEventQ;
};

#endif
