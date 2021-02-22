#ifndef PROTECTEDEVENTQUEUE__H
#define PROTECTEDEVENTQUEUE__H

#include <queue>
#include <string>
#include <mutex>
#include "../common_src/types.h"

class ProtectedEventQueue {
public: 
    event_t pop();
    void push(event_t aString);
    bool isEmpty();
private:
    std::queue<event_t> q;
    std::mutex m;
};


#endif