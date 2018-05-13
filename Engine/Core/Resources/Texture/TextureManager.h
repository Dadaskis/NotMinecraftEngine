#pragma once

#include <map>
#include <string>

class TextureManager {
public:
    static int loadTexture(const std::string& fileName, bool isOpaque);
};
