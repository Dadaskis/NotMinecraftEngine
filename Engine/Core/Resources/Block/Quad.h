#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>

class Quad {
private:
    unsigned int VAO, VBO, EBO, indicesSize;
public:
    Quad();
    Quad(const float* verteces, int vertecesSize, const unsigned int* indices, int indicesSize, unsigned int instanceVBO);
    void draw(int size);
    void deleteGLInfo();
};
