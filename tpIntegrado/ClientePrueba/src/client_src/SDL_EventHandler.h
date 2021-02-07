#ifndef _SDL_EVENT_HANDLER_H_
#define _SDL_EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <atomic>
#include <map>
#include "../common_src/thread.h"
#include "../common_src/types.h"
#include "../common_src/protectedQueue.h"


class SDL_EventHandler : public Thread{
private: 
    std::map<SDL_Keycode, event_t> keyDownEvents;
    std::map<SDL_Keycode, event_t> keyUpEvents;
    ProtectedQueue<event_t> &q;
    std::atomic<bool> is_running;
    std::atomic<bool> quitGameRead;
public:
    SDL_EventHandler(ProtectedQueue<event_t> &q);
    ~SDL_EventHandler();
    event_t pollEvent();
    void exitPollEvent(SDL_Event &SDLEvent, event_t &event);
    void operator()();
    virtual void run() override;
    void stop();
    bool isDead();
    bool finished();
};

#endif
