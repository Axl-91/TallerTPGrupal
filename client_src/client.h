#ifndef CLIENT__T
#define CLIENT__T

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <atomic>
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "clientReceiver.h"
#include "clientTransmitter.h"

class Client{
public:
    Client(const char *host_name, const char *port);
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
};

#endif
