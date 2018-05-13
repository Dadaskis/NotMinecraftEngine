#include "ResourceManager.h"

ResourceManager::ResourceManager(){
    int cameraID = createCamera();
    currentCamera = getCamera(cameraID);
}

int ResourceManager::createShader(const std::string& vertexShader, const std::string& fragmentShader){
    Shader shader(vertexShader.c_str(), fragmentShader.c_str());
    shaders.push_back(shader);
    return shaders.size() - 1;
}

Shader* ResourceManager::getShader(int shaderID){
    return &shaders.at(shaderID);
}

bool ResourceManager::isShaderIDRight(int shaderID){
    if(shaderID >= 0){
        if(shaderID < shaders.size()){
            return true;
        }
    }
    return false;
}


int ResourceManager::createCamera(){
    cameras.push_back(Camera());
    return cameras.size() - 1;
}

Camera* ResourceManager::getCamera(int cameraID){
    return &cameras.at(cameraID);
}

bool ResourceManager::isCameraIDRight(int cameraID){
    if(cameraID >= 0){
        if(cameraID < cameras.size()){
            return true;
        }
    }
    return false;
}

Camera* ResourceManager::getCurrentCamera(){
    return currentCamera;
}

void ResourceManager::setCurrentCamera(int cameraID){
    currentCamera = &cameras.at(cameraID);
}


int ResourceManager::createBlockSystem(){
    BSs.push_back(BlockSystem());
    return BSs.size() - 1;
}

BlockSystem* ResourceManager::getBlockSystem(int blockSystemID){
    return &BSs.at(blockSystemID);
}

bool ResourceManager::isBlockSystemIDRight(int blockSystemID){
    if(blockSystemID >= 0){
        if(blockSystemID < BSs.size()){
            return true;
        }
    }
    return false;
}


int ResourceManager::createThread(){
    threads.push_back(std::thread());
    return threads.size() - 1;
}

std::thread* ResourceManager::getThread(int threadID){
    return &threads.at(threadID);
}

void ResourceManager::startThread(int threadID){
    threads.at(threadID).detach();
}

void ResourceManager::setThreadFunction(int threadID, std::function<void()> function){
    threads.at(threadID) = std::thread(function);
}

bool ResourceManager::isThreadIDRight(int threadID){
    if(threadID >= 0){
        if(threadID < threads.size()){
            return true;
        }
    }
    return false;
}
