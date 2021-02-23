#include "AILuaScript.h"

bool CheckLua(lua_State *L, int r){
	if (r != LUA_OK){
		std::string errormsg = lua_tostring(L, -1);
		std::cerr << errormsg << std::endl;
		return false;
	}
	return true;
}

AILuaScript::AILuaScript(){
    L = luaL_newstate();
    luaL_openlibs(L);
    (CheckLua(L, luaL_dofile(L, "./Media/Lua/AILuaAction.lua")));

}
AILuaScript::~AILuaScript(){}

void AILuaScript::getIdleEvent(event_t &event, bool &rotating, bool &moving){
    lua_getglobal(L, "getIdleEvent");
    lua_pushboolean(L, rotating);
    lua_pushboolean(L, moving);    

    if(CheckLua(L, lua_pcall(L, 2, 3, 0))){
        event = (event_t)lua_tonumber(L, -3);
        rotating = (bool)lua_toboolean(L, -2);
        moving = (bool)lua_toboolean(L, -1);
    }
}

void AILuaScript::getEvent(event_t &event, float &playerAng,float &enemyAng, float &dist,
                            bool &shooting, bool &rotating, bool &moving){
    
    lua_getglobal(L, "getEvent");
    lua_pushnumber(L, playerAng);
    lua_pushnumber(L, enemyAng);
    lua_pushnumber(L, dist);
    lua_pushboolean(L, shooting);
    lua_pushboolean(L, rotating);
    lua_pushboolean(L, moving);

    if(CheckLua(L, lua_pcall(L, 6, 4, 0))){
        event = (event_t)lua_tonumber(L, -4);
        shooting = (bool)lua_toboolean(L, -3);
        rotating = (bool)lua_toboolean(L, -2);
        moving = (bool)lua_toboolean(L, -1);
    }
}

bool AILuaScript::isVisible(Vector &posPlayer, Vector &posEnemy, float &angPlayer){
    lua_getglobal(L, "objIsVisible");
    lua_pushnumber(L, posPlayer.getX());
    lua_pushnumber(L, posPlayer.getY());
    lua_pushnumber(L, posEnemy.getX());
    lua_pushnumber(L, posEnemy.getY());
    lua_pushnumber(L, angPlayer);

    if(CheckLua(L, lua_pcall(L, 5, 1, 0))){
        return (bool)lua_toboolean(L, -1);
    }
    return false;
}
