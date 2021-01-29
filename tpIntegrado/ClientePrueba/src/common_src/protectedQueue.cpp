#include "protectedQueue.h"

std::string ProtectedQueue::pop(){
    std::unique_lock<std::mutex> lock(m);
    std::string aux(std::move(q.front()));
    q.pop();
    return aux;
}

void ProtectedQueue::push(std::string aString){
    std::unique_lock<std::mutex> lock(m);
    q.push(std::move(aString));
}

bool ProtectedQueue::isEmpty(){
    std::unique_lock<std::mutex> lock(m);
    if(q.empty())
        return true;
    return false;
}
