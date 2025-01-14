#ifndef USER__T
#define USER__T
#include <map>
#include "updateHandler.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "serverReceiver.h"
#include "serverTransmitter.h"
#include "protectedMatchEventQueue.h"
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
    ProtectedQueue<MatchEvent_t> *q;
    std::atomic<bool> started;
    std::string userName;
    size_t ID;
public:
    void updateMissile(Missile_t m); 

    User(Socket socket);
    void operator()();
    void setProtectedMatchEventQueue(ProtectedQueue<MatchEvent_t> *q);
    std::string getName();
    virtual void run() override;
    void readEvent(event_t &event);
    void readMenuEvent(menu_event_t &menuEvent);
    // void readInput(std::string &input);
    void stop();
    bool is_dead();
    void sendGameUpdate(update_tag_t &aTag);
    bool hasStarted();
    void changeName(std::string &newName);
    void sendMap(std::vector<std::vector<int>> &lvl1);
    void sendPlayerInfo(Player_t &player);
    void update(UpdateHandler &uHandler);
    void sendMapUpdate(Map_change_t &aMapChange);
    void setID(size_t ID);
    void sendString(std::string &aString);
};

#endif
