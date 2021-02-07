#ifndef PROTECTEDMATCHEVENTQUEUE__H
#define PROTECTEDMATCHEVENTQUEUE__H

#include <queue>
#include <string>
#include <mutex>
#include "../common_src/types.h"

class ProtectedMatchEventQueue {
public: 
    MatchEvent_t pop();
    void push(MatchEvent_t aString);
    bool isEmpty();
private:
    std::queue<MatchEvent_t> q;
    std::mutex m;
};


#endif