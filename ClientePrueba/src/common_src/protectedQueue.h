#ifndef PROTECTEDQUEUE__T
#define PROTECTEDQUEUE__T

#include <queue>
#include <string>
#include <mutex>
#include <iostream>

template <class T>
class ProtectedQueue {
public: 
    T pop(){
        std::unique_lock<std::mutex> lock(m);
        T aux(std::move(q.front()));
        q.pop();
        return aux;
    }
    void push(T obj){
        std::unique_lock<std::mutex> lock(m);
        q.push(std::move(obj));
    }
    bool isEmpty(){
        std::unique_lock<std::mutex> lock(m);
        if(q.empty())
            return true;
        return false;
    }
private:
    std::queue<T> q;
    std::mutex m;
};

#endif