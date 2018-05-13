#include "glad/glad.h"
#include "TextureUtilities.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

unsigned int TextureUtils::createTexture(const std::string& fileNameStr, bool isOpaque) {
    const char* fileName = fileNameStr.c_str();
    int format = GL_RGBA;

    int params;
    if(isOpaque){
        params = GL_REPEAT;
    }else{
        params = GL_CLAMP_TO_EDGE;
    }

    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texture);
    }
    stbi_image_free(data);

    return texture;
}
