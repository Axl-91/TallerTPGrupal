#ifndef CLIENTTRANSMITTER__T
#define CLIENTTRANSMITTER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "../server_src/protectedQueue.h"

class ClientTransmitter : public Thread {
public:
    ClientTransmitter(Socket &socket);
    ClientTransmitter(ClientTransmitter&& other);
    void operator()();
    bool isRunning();
    virtual void run() override;
    void isAtMenu();
    void isInMatch();
private:
    Socket &socket;
    std::atomic<bool> is_running;
    ProtectedQueue q;
    std::atomic<bool> atMenus;
};

#endif
