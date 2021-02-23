#ifndef AILUASCRIPT__H
#define AILUASCRIPT__H

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

#include "../common_src/types.h"
#include "../common_src/Vector.h"

class AILuaScript{
public:
    AILuaScript();
    ~AILuaScript();
    void getIdleEvent(event_t &event, bool &rotating, bool &moving);
    bool isVisible(Vector &posPlayer, Vector &posEnemy, float &playerAng);
    void getEvent(event_t &event, float &angPlayer,float &relativeAng, float &dist,
                            bool &shooting, bool &rotating, bool &moving);
private:
    lua_State *L;
};

#endif