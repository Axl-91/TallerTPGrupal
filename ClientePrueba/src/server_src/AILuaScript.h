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
    void getEvent(event_t &event);
    bool isVisible(Vector &posPlayer, Vector &posEnemy, float &isVisible);
    void isVisible2(float x, float y, float ex, float ey, float angPlayer);
    void printHello();
private:
    lua_State *L;
};

#endif
