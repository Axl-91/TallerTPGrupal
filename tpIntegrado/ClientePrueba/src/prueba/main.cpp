#include <iostream>
#include <thread>
#include <chrono>

#include <time.h>
#include "Vector.h"

int main(void){
    // long int start = 0, end = 0;
    // double delta = 0;
    // double ns = 1000000.0 / 60.0; // Syncs updates at 60 per second (59 - 61)
    int quit= 100;
    int c=0;

    // time_t timer1;
    // time_t timer2;

    // auto initial = std::chrono::high_resolution_clock::now();
    while (c<=quit) {

        auto initial = std::chrono::high_resolution_clock::now();

        while(c<=100000){ 
            c++;
            std::cout<<"c: "<<c<<std::endl;
        }
        auto final = std::chrono::high_resolution_clock::now();
        auto loopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
        // long sleepTime = timeStep - loopDuration.count();
        // if (sleepTime > 0) {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        // std::cout<<"duracion: "<<loopDuration.count()<<std::endl;

    }


}