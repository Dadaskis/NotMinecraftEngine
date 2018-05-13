#include "Block.h"
#include "Quad.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

BlockSystem::BlockSystem(){
    glGenBuffers(1, &instanceVBO);

    {
        float verteces[] = {
            -size, -size, -size, 0.0f, 0.0f,
             size, -size, -size, 1.0f, 0.0f,
            -size, -size,  size, 0.0f, 1.0f,
             size, -size,  size, 1.0f, 1.0f
        };

        unsigned int indices[] = {0, 1, 2, 1, 3, 2};

        quads[BLOCK_DOWN] = Quad(&verteces[0], 20, &indices[0], 6, instanceVBO);
    }

    {
        float verteces[] = {
            -size,  size, -size, 0.0f, 0.0f,
             size,  size, -size, 1.0f, 0.0f,
            -size,  size,  size, 0.0f, 1.0f,
             size,  size,  size, 1.0f, 1.0f
        };

        unsigned int indices[] = {0, 2, 1, 1, 2, 3};

        quads[BLOCK_UP] = Quad(&verteces[0], 20, &indices[0], 6, instanceVBO);
    }

    {
        float verteces[] = {
            -size, -size, -size, 0.0f, 0.0f,
             size, -size, -size, 1.0f, 0.0f,
            -size,  size, -size, 0.0f, 1.0f,
             size,  size, -size, 1.0f, 1.0f
        };

        unsigned int indices[] = {0, 2, 1, 1, 2, 3};

        quads[BLOCK_LEFT] = Quad(&verteces[0], 20, &indices[0], 6, instanceVBO);
    }

    {
        float verteces[] = {
             size,   size, -size, 1.0f, 1.0f,
             size,   size,  size, 0.0f, 1.0f,
             size,  -size, -size, 1.0f, 0.0f,
             size,  -size,  size, 0.0f, 0.0f
        };

        unsigned int indices[] = {0, 1, 2, 1, 3, 2};

        quads[BLOCK_FRONT] = Quad(&verteces[0], 20, &indices[0], 6, instanceVBO);
    }

    {
        float verteces[] = {
             -size, -size, -size, 0.0f, 0.0f,
             -size, -size,  size, 1.0f, 0.0f,
             -size,  size, -size, 0.0f, 1.0f,
             -size,  size,  size, 1.0f, 1.0f
        };

        unsigned int indices[] = {0, 1, 2, 1, 3, 2};

        quads[BLOCK_BACK] = Quad(&verteces[0], 20, &indices[0], 6, instanceVBO);
    }

    {
        float verteces[] = {
            -size,  size,  size, 1.0f, 1.0f,
             size,  size,  size, 0.0f, 1.0f,
            -size, -size,  size, 1.0f, 0.0f,
             size, -size,  size, 0.0f, 0.0f
        };

        unsigned int indices[] = {0, 2, 1, 1, 2, 3};

        quads[BLOCK_RIGHT] = Quad(&verteces[0], 20, &indices[0], 6, instanceVBO);
    }
}

void BlockSystem::deleteOpenGLInfo(){
    for(int index = 0; index < 6; index++){
        quads[index].deleteGLInfo();
    }
    delete quads;
}

void BlockSystem::add(glm::mat4 position){
    positions.push_back(position);
}

void BlockSystem::draw(){
    shader->use();

    int width, height;
    window->getSize(&width, &height);

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->getFOV()), (float)(width) / (float)(height), 0.1f, 1000.0f);

    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setInt("baseTexture", 0);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::mat4), &positions[0], GL_STREAM_DRAW);

    int size = positions.size();
    for(int index = 0; index < 6; index++){
        glBindTexture(GL_TEXTURE_2D, textures[index]);
        quads[index].draw(size);
    }
}

void BlockSystem::clear(){
    positions = std::vector<glm::mat4>();
}

void BlockSystem::setTexture(int direction, int texture){
    if(direction == BLOCK_ALL){
        for(int index = 0; index < 6; index++){
            textures[index] = texture;
        }
    }else{
        if(direction >= 0 & direction < 6){
            textures[direction] = texture;
        }
    }
}

void BlockSystem::setShader(Shader* shader){
    this->shader = shader;
}

void BlockSystem::setCamera(Camera* camera){
    this->camera = camera;
}

void BlockSystem::setWindow(Window* window){
    this->window = window;
}
