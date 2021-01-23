#ifndef CLIENTRECEIVER__T
#define CLIENTRECEIVER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "../server_src/protectedQueue.h"


class ClientReceiver : public Thread {
public:
    ClientReceiver(Socket &socket);
    ClientReceiver(ClientReceiver&& other);
    void operator()();
    virtual void run() override;
    void stop();
    void isAtMenu();
    void isInMatch();
    void receiveMenuOption();
    void receiveGame();
private:
    Socket &socket;
    std::atomic<bool> is_running;
    std::atomic<bool> atMenus;
};

#endif
