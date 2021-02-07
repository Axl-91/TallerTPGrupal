#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <time.h>
#include "Vector.h"

int main(void){
    std::queue<int> q;
    q.push(1);
    q.push(2);
    std::cout<<q.front()<<std::endl;
    std::cout<<q.back()<<std::endl;

}