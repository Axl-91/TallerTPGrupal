#ifndef _TIME_EVENT_HANDLER_H_
#define _TIME_EVENT_HANDLER_H_

#include <map>


typedef struct 
{
    int timer;
    /* data */
}Time_event;

typedef enum{
    TET_OPEN_DOOR,

}time_event_type;


class TimeEventHandler{
    std::map<int, Time_event> events;

public:
    TimeEventHandler();
    ~TimeEventHandler();

    void timeEvent(Time_event tE);

};




#endif
