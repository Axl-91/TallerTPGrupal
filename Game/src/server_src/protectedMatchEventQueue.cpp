#include "protectedMatchEventQueue.h"

MatchEvent_t ProtectedMatchEventQueue::pop(){
    std::unique_lock<std::mutex> lock(m);
    MatchEvent_t event = q.front();
    q.pop();
    return event;
}

void ProtectedMatchEventQueue::push(MatchEvent_t anEvent){
    std::unique_lock<std::mutex> lock(m);
    q.push(std::move(anEvent));
}

bool ProtectedMatchEventQueue::isEmpty(){
    std::unique_lock<std::mutex> lock(m);
    if(q.empty())
        return true;
    return false;
}
