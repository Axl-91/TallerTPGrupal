#include "protectedQueue.h"
/*
template <class T>
T ProtectedQueue<T>::pop(){
    std::unique_lock<std::mutex> lock(m);
    T aux(std::move(q.front()));
    q.pop();
    return aux;
}

template <class T>
void ProtectedQueue<T>::push(T obj){
    std::unique_lock<std::mutex> lock(m);
    q.push(std::move(obj));
}

template <class T>
bool ProtectedQueue<T>::isEmpty(){
    std::unique_lock<std::mutex> lock(m);
    if(q.empty())
        return true;
    return false;
}
*/