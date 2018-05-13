#include "TextureManager.h"

#include "TextureUtilities.h"

#include <glad/glad.h>

int TextureManager::loadTexture(const std::string& fileName, bool isOpaque){
    int format;
    if(isOpaque){
        format = GL_REPEAT;
    }else{
        format = GL_CLAMP_TO_EDGE;
    }
    return TextureUtils::createTexture(fileName.c_str(), GL_RGBA, format);
}
