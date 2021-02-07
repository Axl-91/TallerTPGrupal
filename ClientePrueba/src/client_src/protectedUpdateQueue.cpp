#include "protectedUpdateQueue.h"

Update_t ProtectedUpdateQueue::pop(){
    std::unique_lock<std::mutex> lock(m);
    Update_t anUpdate = q.front();
    q.pop();
    return anUpdate;
}

void ProtectedUpdateQueue::push(Update_t anUpdate){
    std::unique_lock<std::mutex> lock(m);
    q.push(std::move(anUpdate));
}

bool ProtectedUpdateQueue::isEmpty(){
    std::unique_lock<std::mutex> lock(m);
    if(q.empty())
        return true;
    return false;
}
