#ifndef USER__T
#define USER__T
#include <map>
#include "updateHandler.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "serverReceiver.h"
#include "serverTransmitter.h"
#include "../common_src/protectedEventQueue.h"
#include <string>
#include <vector>
#include <sstream>
// #include <fstream>
#include <utility>
#include <atomic>
#include "../common_src/types.h"
class User : public Thread{
private:
    Socket s;
    ServerTransmitter transmitter;
    ServerReceiver receiver;
    std::atomic<bool> userIsRunning;
    ProtectedEventQueue *q;
    std::atomic<bool> started;
    std::string userName;
    size_t ID;
public:
    User(Socket socket);
    void operator()();
    void setProtectedEventQueue(ProtectedEventQueue *q);
    std::string getName();
    virtual void run() override;
    void readInput(event_t &input);
    // void readInput(std::string &input);
    void stop();
    bool is_dead();
    void sendGameUpdate(std::stringstream& game);
    bool hasStarted();
    void changeName(std::string newName);
    void sendMap(std::vector<std::vector<int>> &lvl1);
    void sendPlayerInfo(Player_t player);
    void update(UpdateHandler uHandler);
    void sendMapUpdate(Map_change_t &aMapChange);

};

#endif
