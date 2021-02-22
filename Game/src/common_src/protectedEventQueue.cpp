#include "protectedEventQueue.h"

event_t ProtectedEventQueue::pop(){
    std::unique_lock<std::mutex> lock(m);
    event_t event = q.front();
    q.pop();
    return event;
}

void ProtectedEventQueue::push(event_t anEvent){
    std::unique_lock<std::mutex> lock(m);
    q.push(std::move(anEvent));
}

bool ProtectedEventQueue::isEmpty(){
    std::unique_lock<std::mutex> lock(m);
    if(q.empty())
        return true;
    return false;
}
