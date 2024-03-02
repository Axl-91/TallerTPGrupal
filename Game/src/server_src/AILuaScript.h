#ifndef AILUASCRIPT__H
#define AILUASCRIPT__H

extern "C" {
# include "lua5.3/lua.h"
# include "lua5.3/lauxlib.h"
# include "lua5.3/lualib.h"
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