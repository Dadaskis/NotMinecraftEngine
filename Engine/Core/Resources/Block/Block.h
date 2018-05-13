#pragma once

#include <glm/glm.hpp>
#include <array>
#include <vector>

#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../../Window/Window.h"
#include "Quad.h"

enum blockDirections {
    BLOCK_DOWN,
    BLOCK_UP,
    BLOCK_LEFT,
    BLOCK_RIGHT,
    BLOCK_BACK,
    BLOCK_FRONT,
    BLOCK_ALL
};

class BlockSystem {
private:
    unsigned int instanceVBO = 0;
    std::vector<glm::mat4> positions;

    Quad* quads = new Quad[6];
    int* textures = new int[6];
    Shader* shader;
    Camera* camera;
    Window* window;
    const float size = 0.49999f;
public:
    BlockSystem();
    void deleteOpenGLInfo();

    void add(glm::mat4 position);
    void draw();
    void clear();
    void setTexture(int direction, int texture);
    void setShader(Shader* shader);
    void setCamera(Camera* camera);
    void setWindow(Window* window);
};
