#ifndef THREAD__T
#define THREAD__T

#include <thread>

class Thread{
public:
    Thread();
    virtual ~Thread();
    Thread(const Thread&)=delete;
    Thread& operator=(const Thread&)=delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
    void start();
    void join();
    virtual void run() = 0;

private:
    std::thread thread;
};

#endif
