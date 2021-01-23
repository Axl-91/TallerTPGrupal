#ifndef USER__T
#define USER__T
#include <map>
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "serverReceiver.h"
#include "serverTransmitter.h"
#include "protectedQueue.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <atomic>

class User : public Thread{
private:
    Socket s;
    ServerTransmitter transmitter;
    ServerReceiver receiver;
    std::atomic<bool> userIsRunning;
    ProtectedQueue *q;
    std::atomic<bool> started;
    std::string userName;

public:
    User(Socket socket);
    void operator()();
    void setProtectedQueue(ProtectedQueue *q);
    std::string getName();
    virtual void run() override;
    void readInput(std::string &input);
    void stop();
    bool is_dead();
    void sendGameUpdate(std::stringstream& game);
    bool hasStarted();
    void changeName(std::string newName);
};

#endif
