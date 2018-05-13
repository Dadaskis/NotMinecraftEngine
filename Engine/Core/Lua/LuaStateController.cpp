#include "LuaStateController.h"
#include <LuaBridge/LuaBridge.h>

LuaStateController::LuaStateController(){
    luaL_openlibs(lua);
}

void LuaStateController::doFile(const std::string& name){
    luaL_dofile(lua, name.c_str());
    lua_pcall(lua, 0, 0, 0);
}

int LuaStateController::getGlobalInt(const std::string& name){
    luabridge::LuaRef numberAtLua = luabridge::getGlobal(lua, name.c_str());
    int number = numberAtLua.cast<int>();
    return number;
}

std::string LuaStateController::getGlobalString(const std::string& name){
    luabridge::LuaRef stringAtLua = luabridge::getGlobal(lua, name.c_str());
    std::string string = stringAtLua.cast<std::string>();
    return string;
}

lua_State* LuaStateController::getLuaState(){
    return lua;
}
