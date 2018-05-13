#pragma once

#include "Window/Window.h"
#include "Resources/ResourceManager.h"
#include "Lua/LuaStateController.h"

struct Core{
    Window window;
    ResourceManager RM;
    LuaStateController lua;
};
