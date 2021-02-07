#ifndef PROTECTEDQUEUE__T
#define PROTECTEDQUEUE__T

#include <queue>
#include <string>
#include <mutex>
class ProtectedQueue {
public: 
    std::string pop();
    void push(std::string aString);
    bool isEmpty();
private:
    std::queue<std::string> q;
    std::mutex m;
};

#endif