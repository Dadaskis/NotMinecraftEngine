#pragma once

#include <lua.hpp>
#include <string>

class LuaStateController{
private:
    lua_State* lua = luaL_newstate();
public:
    LuaStateController();

    lua_State* getLuaState();

    void doFile(const std::string& name);

    int getGlobalInt(const std::string& name);
    std::string getGlobalString(const std::string& name);
};
