#pragma once

#include <string>

class TextureUtils {
public:
    static unsigned int createTexture(const std::string& fileNameStr, bool isOpaque);
};
