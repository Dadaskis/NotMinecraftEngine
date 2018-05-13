#include "Window.h"

#include "../Lua/LuaStateController.h"

#include <iostream>

Camera* Window::currentCamera;

float lastX = 0.0f, lastY = 0.0f, xOffset, yOffset;

void mouseCallback(GLFWwindow* window, double xAngle, double yAngle){
    xOffset = xAngle - lastX;
    yOffset = lastY - yAngle;

    lastX = xAngle;
    lastY = yAngle;

    Window::currentCamera->processMouseMovement(xOffset, yOffset);
}

void Window::createWindow(const std::string& windowTitle, int width, int height, std::function<void()> preMainLoopFunction, std::function<void()> mainLoopFunction){
    const char* title = windowTitle.c_str();

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == NULL){
        std::cout << "Window error" << std::endl;
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "GLAD error" << std::endl;
        exit(-1);
    }

    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    preMainLoopFunction();
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.15f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainLoopFunction();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

bool Window::isKeyPressed(int keyID){
    if(glfwGetKey(window, keyID) == GLFW_PRESS){
        return true;
    }
    return false;
}

void Window::getSize(int* width, int* height){
    glfwGetWindowSize(window, width, height);
}

void Window::setCamera(Camera* camera){
    currentCamera = camera;
}
