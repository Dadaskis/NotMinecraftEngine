#include "LuaStateController.h"
#include <LuaBridge/LuaBridge.h>
#include <iostream>

void LuaStateController::doFile(int stateID, const std::string& name){
    luaL_dofile(getLuaState(stateID), name.c_str());
    lua_pcall(getLuaState(stateID), 0, 0, 0);
}

int LuaStateController::getGlobalInt(int stateID, const std::string& name){
    luabridge::LuaRef numberAtLua = luabridge::getGlobal(getLuaState(stateID), name.c_str());
    int number = numberAtLua.cast<int>();
    return number;
}

std::string LuaStateController::getGlobalString(int stateID, const std::string& name){
    luabridge::LuaRef stringAtLua = luabridge::getGlobal(getLuaState(stateID), name.c_str());
    std::string string = stringAtLua.cast<std::string>();
    return string;
}

int LuaStateController::createState(std::function<void(LuaState* state)> addFunctions, const std::string& directory){
    LuaState* luaState = new LuaState();
    int stateID = states.size();
    luaState->stateThread = std::thread([luaState, addFunctions, stateID, directory](){
        int stateIDNumber = stateID;
        luaState->state = luaL_newstate();
        luaL_openlibs(luaState->state);
        addFunctions(luaState);
        luabridge::getGlobalNamespace(luaState->state)
            .beginNamespace("LUA_STATS")
                .addVariable("STATE_ID", &stateIDNumber, false)
            .endNamespace();
        luaL_dofile(luaState->state, "gamedata\\EngineConstants.lua");
        lua_pcall(luaState->state, 0, 0, 0);
        std::string newDirectory = directory + "\\Starter.lua";
        luaL_dofile(luaState->state, newDirectory.c_str());
        lua_pcall(luaState->state, 0, 0, 0);
    });
    states.push_back(luaState);
    luaState->stateThread.detach();
    return stateID;
}

lua_State* LuaStateController::getLuaState(int stateID){
    return states.at(stateID)->state;
}
