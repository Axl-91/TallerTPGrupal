#ifndef PROTECTEDQUEUE__T
#define PROTECTEDQUEUE__T

#include <queue>
#include <string>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <atomic>

template <class T>
class ProtectedQueue {
public: 
    ProtectedQueue(): closed(false){}

    void pop(T &poppedValue){
        std::unique_lock<std::mutex> lock(m);
        while (!closed && q.empty())
        // while (q.empty())
            cv.wait(lock);

        if(closed && q.empty()){
            return;
}
        poppedValue = std::move(q.front());
        q.pop();
    }
    void push(T obj){
        std::unique_lock<std::mutex> lock(m);
        q.push(std::move(obj));
        cv.notify_all();
    }
    // bool isEmpty(){
    //     std::unique_lock<std::mutex> lock(m);
    //     if(q.empty())
    //         return true;
    //     return false;
    // }
    void close(){
        closed = true;
        cv.notify_all();
    }
    // void pichula(){
        
    // }
private:
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cv;
    std::atomic<bool> closed;
};

#endif