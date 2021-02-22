#ifndef MATCHEVENTREADER__H
#define MATCHEVENTREADER__H

#include <atomic>
#include <map>
#include "../common_src/thread.h"
#include "../common_src/types.h"
#include "../common_src/protectedQueue.h"
#include "serverPlayer.h"

class MatchEventReader : public Thread{
public:
    MatchEventReader(std::map<size_t, ServerPlayer> &p,
                    ProtectedQueue<MatchEvent_t> &aQueue);
    virtual void run() override;
    void operator()();
    void stop();
    bool isDead();
private:
    std::map<size_t, ServerPlayer> &players;
    ProtectedQueue<MatchEvent_t> &q;
    std::atomic<bool> is_running;
    void readEvent();
};

#endif
