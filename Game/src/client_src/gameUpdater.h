#ifndef GAMEUPDATER__H
#define GAMEUPDATER__H

#include "../common_src/thread.h"
#include "../common_src/types.h"
#include "../common_src/protectedQueue.h"
#include "Player.h"

class GameUpdater : public Thread {
private:
    std::mutex &m;
    std::atomic<bool> is_running;
	Player &player;
	ProtectedQueue<Update_t> &uQ;
    Map &mapGame;
    void update();
    void updatePlayer(Player_t &p);
    void updateMap(Map_change_t &aMapChange);
    void updateMissile(Missile_t &m);

public:
    GameUpdater(Player &player, 
                ProtectedQueue<Update_t> &aQueue, 
                Map &mapGame, std::mutex &mut);
    void operator()();
    virtual void run() override;
    void stop();
};

#endif
