#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <thread>
#include <string>
#include <vector>
#include <functional>

struct LuaState {
    lua_State* state;
    std::thread stateThread;
};

class LuaStateController{
private:
    std::vector<LuaState*> states;
public:
    int createState(std::function<void(LuaState* state)> addFunctions, const std::string& directory);
    lua_State* getLuaState(int stateID);

    void doFile(int stateID, const std::string& name);

    int getGlobalInt(int stateID, const std::string& name);
    std::string getGlobalString(int stateID, const std::string& name);
};
