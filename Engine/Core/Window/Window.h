#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "../Resources/Camera/Camera.h"

class Window{
private:
    GLFWwindow* window;
public:
    static Camera* currentCamera;

    void createWindow(const std::string& windowTitle, int width, int height);
    void start();
    static void setCamera(Camera* camera);
    bool isKeyPressed(int keyID);
    void getSize(int* width, int* height);
};
