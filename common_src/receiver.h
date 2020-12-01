#ifndef RECEIVER__T
#define RECEIVER__T

#include <vector>
#include <sstream>
#include <atomic>
#include "thread.h"
#include "socket.h"

class Receiver : public Thread {
public:
    Receiver(Socket &socket, std::stringstream& response);

    void operator()();

    virtual void run() override;
private:
    Socket &socket;
    std::stringstream &response;
    std::atomic<bool> is_running;
};

#endif
