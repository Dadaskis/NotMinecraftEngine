#pragma once

#include <thread>
#include <vector>
#include <string>

#include "Shader/Shader.h"
#include "Camera/Camera.h"
#include "Block/Block.h"

class ResourceManager {
private:
    std::vector<Shader> shaders;
    std::vector<Camera> cameras;
    std::vector<BlockSystem> BSs;
    std::vector<std::thread> threads;
    Camera* currentCamera;
public:
    ResourceManager();

    int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    Shader* getShader(int shaderID);
    bool isShaderIDRight(int shaderID);

    int createCamera();
    Camera* getCamera(int cameraID);
    Camera* getCurrentCamera();
    bool isCameraIDRight(int cameraID);
    void setCurrentCamera(int cameraID);

    int createBlockSystem();
    BlockSystem* getBlockSystem(int blockSystemID);
    bool isBlockSystemIDRight(int blockSystemID);

    int createThread();
    std::thread* getThread(int threadID);
    void startThread(int threadID);
    void setThreadFunction(int threadID, std::function<void()> function);
    bool isThreadIDRight(int threadID);
};
