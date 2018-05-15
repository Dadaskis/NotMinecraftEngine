#pragma once

#include "Window/Window.h"
#include "Resources/ResourceManager.h"
#include "Lua/LuaStateController.h"
#include "Noise/FastNoise.h"
#include <vector>

struct Core{
    Window window;
    ResourceManager RM;
    LuaStateController lua;
    FastNoise noise;
};
