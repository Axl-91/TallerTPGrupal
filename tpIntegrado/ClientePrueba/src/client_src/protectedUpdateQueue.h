#ifndef PROTECTEDUPDATEQUEUE__H
#define PROTECTEDUPDATEQUEUE__H

#include <queue>
#include <string>
#include <mutex>
#include "../common_src/types.h"

class ProtectedUpdateQueue {
public: 
    Update_t pop();
    void push(Update_t anUpdate);
    bool isEmpty();
private:
    std::queue<Update_t> q;
    std::mutex m;
};


#endif