#ifndef TRANSMITTER__T
#define TRANSMITTER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "thread.h"
#include "socket.h"

class Transmitter : public Thread {
public:
    Transmitter(Socket &socket, std::stringstream& response);
    
    void operator()();

    virtual void run() override;
private:
    Socket &socket;
    std::stringstream &response;
    std::atomic<bool> is_running;
};

#endif
