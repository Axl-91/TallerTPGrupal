#include "AILuaScript.h"

bool CheckLua(lua_State *L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

AILuaScript::AILuaScript(){
    // clientId(clientId){
    L = luaL_newstate();
    luaL_openlibs(L);
    if(CheckLua(L, luaL_dofile(L, "./Media/Lua/AILuaAction.lua")))
	{      
        std::cout << "lo abri" << std::endl;
    }
    // luaL_dofile(L, "Lua/AILuaAction.lua");
}
AILuaScript::~AILuaScript(){}


// AILuaScript::LuaScript(std::string& clientId, std::string& scriptFile) :
    // clientId(clientId){
    // L = luaL_newstate();
    // luaL_openlibs(L);

    // luaL_dofile(L, scriptFile.c_str());
    // luaL_dofile(L, scriptFile.c_str());

void AILuaScript::getEvent(event_t &event){
    
    lua_getglobal(L, "getEvent");
    // lua_pushnumber(L, ang);
}

bool AILuaScript::isVisible(Vector &posPlayer, Vector &posEnemy, float &angPlayer){
    std::cout << "entre a isVisible" << std::endl;
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


void AILuaScript::printHello(){
    std::cout << "entre a print" << std::endl;
    // lua_getglobal(L, "helloWorld");
    if(CheckLua(L, luaL_dofile(L, "Media/Lua/AILuaAction.lua")))
	{      
        std::cout << "lo abri" << std::endl;
    }
    // luaL_dofile(L, "Lua/AILuaAction.lua");
    // lua_pushstring (L, "helloWorld");
    // lua_pcall(L, 0, 0, 0);
}
