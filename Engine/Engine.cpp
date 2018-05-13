#include "Engine.h"
#include "Core/Resources/Texture/TextureUtilities.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Core Engine::core;

FastNoise Engine::noise(0);

void Engine::preMainLoopFunction(){
    core.lua.doFile("gamedata\\Types.lua");
}

void Engine::mainLoopFunction(){
    core.lua.doFile("gamedata\\MainLoop.lua");
}

void Engine::start(){
    luabridge::getGlobalNamespace(core.lua.getLuaState())
        .beginNamespace("Engine")
            .addFunction("createShader", createShader)
            .addFunction("createBlockSystem", createBlockSystem)
            .addFunction("addBlockInfo", addBlockInfo)
            .addFunction("setBlockTexture", setBlockTexture)
            .addFunction("setBlockSystemShader", setBlockSystemShader)
            .addFunction("setCameraToBlockSystem", setCameraToBlockSystem)
            .addFunction("drawBlocks", drawBlocks)
            .addFunction("clearBlocksData", clearBlocksData)
            .addFunction("loadTexture", loadTexture)
            .addFunction("isPressed", isPressed)
            .addFunction("handleCamera", handleCamera)
            .addFunction("handleCurrentCamera", handleCurrentCamera)
            .addFunction("getCameraPosition", getCameraPosition)
            .addFunction("getCurrentCameraPosition", getCurrentCameraPosition)
            .addFunction("getCameraFront", getCameraFront)
            .addFunction("getCurrentCameraFront", getCurrentCameraFront)
            .addFunction("getCameraSensitivity", getCameraSensitivity)
            .addFunction("getCurrentCameraSensitivity", getCurrentCameraSensitivity)
            .addFunction("getCameraSpeed", getCameraSpeed)
            .addFunction("getCurrentCameraSpeed", getCurrentCameraSpeed)
            .addFunction("getCameraFOV", getCameraFOV)
            .addFunction("getCurrentCameraFOV", getCurrentCameraFOV)
            .addFunction("getCameraRotation", getCameraRotation)
            .addFunction("getCurrentCameraRotation", getCurrentCameraRotation)
            .addFunction("setCameraRotation", setCameraRotation)
            .addFunction("setCurrentCameraRotation", setCurrentCameraRotation)
            .addFunction("setCameraSensitivity", setCameraSensitivity)
            .addFunction("setCurrentCameraSensitivity", setCurrentCameraSensitivity)
            .addFunction("setCameraFOV", setCameraFOV)
            .addFunction("setCurrentCameraFOV", setCurrentCameraFOV)
            .addFunction("setCameraRotation", setCameraRotation)
            .addFunction("setCurrentCameraRotation", setCurrentCameraRotation)
            .addFunction("setCameraSpeed", setCameraSpeed)
            .addFunction("setCurrentCameraSpeed", setCurrentCameraSpeed)
            .addFunction("setCameraPosition", setCameraPosition)
            .addFunction("setCurrentCameraPosition", setCurrentCameraPosition)
            .addFunction("setNoiseSeed", setNoiseSeed)
            .addFunction("setNoiseType", setNoiseType)
            .addFunction("setNoiseFrequency", setNoiseFrequency)
            .addFunction("setCellurarDistanceFunction", setCellularDistanceFunction)
            .addFunction("setCellularJitter", setCellularJitter)
            .addFunction("setCellularReturnType", setCellularReturnType)
            .addFunction("setFractalGain", setFractalGain)
            .addFunction("setFractalLacunarity", setFractalLacunarity)
            .addFunction("setFractalOctaves", setFractalOctaves)
            .addFunction("setFractalType", setFractalType)
            .addFunction("setInterp", setInterp)
            .addFunction("getNoise", getNoise)
            .addFunction("createThread", createThread)
            .addFunction("startThread", startThread)
            .addFunction("setThreadFunction", setThreadFunction)
        .endNamespace();

    core.lua.doFile("Config.lua");
    std::string title = core.lua.getGlobalString("WINDOW_TITLE");
    int width = core.lua.getGlobalInt("WINDOW_WIDTH"),
        height = core.lua.getGlobalInt("WINDOW_HEIGHT");

    core.window.setCamera(core.RM.getCurrentCamera());
    core.window.createWindow(title, width, height, preMainLoopFunction, mainLoopFunction);
}


int Engine::createShader(const std::string& vertexShader, const std::string& fragmentShader){
    return core.RM.createShader(vertexShader, fragmentShader);
}


int Engine::createBlockSystem(){
    int BSID = core.RM.createBlockSystem();
    core.RM.getBlockSystem(BSID)->setWindow(&core.window);
    return BSID;
}

void Engine::addBlockInfo(int blockSystemID, int X, int Y, int Z){
    if(core.RM.isBlockSystemIDRight(blockSystemID)){
        glm::mat4 position = glm::mat4(1.0f);
        position = glm::translate(position, glm::vec3(X, Y, Z));
        core.RM.getBlockSystem(blockSystemID)->add(position);
    }
}

void Engine::setBlockTexture(int direction, int blockSystemID, int textureID){
    if(core.RM.isBlockSystemIDRight(blockSystemID)){
        core.RM.getBlockSystem(blockSystemID)->setTexture(direction, textureID);
    }
}

void Engine::setBlockSystemShader(int blockSystemID, int shaderID){
    if(core.RM.isBlockSystemIDRight(blockSystemID)){
        Shader* shader = core.RM.getShader(shaderID);
        core.RM.getBlockSystem(blockSystemID)->setShader(shader);
    }
}

void Engine::setCameraToBlockSystem(int cameraID, int blockSystemID){
    core.RM.getBlockSystem(blockSystemID)->setCamera(core.RM.getCamera(cameraID));
}

void Engine::drawBlocks(int blockSystemID){
    if(core.RM.isBlockSystemIDRight(blockSystemID)){
        core.RM.getBlockSystem(blockSystemID)->draw();
    }
}

void Engine::clearBlocksData(int blockSystemID){
    if(core.RM.isBlockSystemIDRight(blockSystemID)){
        core.RM.getBlockSystem(blockSystemID)->clear();
    }
}


int Engine::loadTexture(const std::string& fileName,  bool isOpaque){
    return TextureUtils::createTexture(fileName, isOpaque);
}

bool Engine::isPressed(int buttonID){
    if(core.window.isKeyPressed(buttonID)){
        return true;
    }
    return false;
}

void Engine::handleCamera(int cameraID, int direction){
    if(core.RM.isCameraIDRight(cameraID)){
        core.RM.getCamera(cameraID)->processKeyboard(direction);
    }
}

void Engine::handleCurrentCamera(int direction){
    core.RM.getCurrentCamera()->processKeyboard(direction);
}

luabridge::LuaRef Engine::getCameraPosition(int cameraID){
    if(core.RM.isCameraIDRight(cameraID)){
        glm::vec3 cameraPosition = core.RM.getCamera(cameraID)->getPosition();
        luabridge::LuaRef returnPosition = luabridge::newTable(core.lua.getLuaState());
        returnPosition["X"] = cameraPosition.x;
        returnPosition["Y"] = cameraPosition.y;
        returnPosition["Z"] = cameraPosition.z;
        return returnPosition;
    }
}

luabridge::LuaRef Engine::getCurrentCameraPosition(){
    glm::vec3 cameraPosition = core.RM.getCurrentCamera()->getPosition();
    luabridge::LuaRef returnPosition = luabridge::newTable(core.lua.getLuaState());
    returnPosition["X"] = cameraPosition.x;
    returnPosition["Y"] = cameraPosition.y;
    returnPosition["Z"] = cameraPosition.z;
    return returnPosition;
}

luabridge::LuaRef Engine::getCameraFront(int cameraID){
    if(core.RM.isCameraIDRight(cameraID)){
        glm::vec3 cameraFront = core.RM.getCamera(cameraID)->getFront();
        luabridge::LuaRef returnFront = luabridge::newTable(core.lua.getLuaState());
        returnFront["X"] = cameraFront.x;
        returnFront["Y"] = cameraFront.y;
        returnFront["Z"] = cameraFront.z;
        return returnFront;
    }
}

luabridge::LuaRef Engine::getCurrentCameraFront(){
    glm::vec3 cameraFront = core.RM.getCurrentCamera()->getFront();
    luabridge::LuaRef returnFront = luabridge::newTable(core.lua.getLuaState());
    returnFront["X"] = cameraFront.x;
    returnFront["Y"] = cameraFront.y;
    returnFront["Z"] = cameraFront.z;
    return returnFront;
}

float Engine::getCameraSensitivity(int cameraID){
    if(core.RM.isCameraIDRight(cameraID)){
        return core.RM.getCamera(cameraID)->getMouseSensitivity();
    }
}
float Engine::getCurrentCameraSensitivity(){
    return core.RM.getCurrentCamera()->getMouseSensitivity();
}

float Engine::getCameraSpeed(int cameraID){
    if(core.RM.isCameraIDRight(cameraID)){
        return core.RM.getCamera(cameraID)->getSpeed();
    }
}
float Engine::getCurrentCameraSpeed(){
    return core.RM.getCurrentCamera()->getSpeed();
}

float Engine::getCameraFOV(int cameraID){
    if(core.RM.isCameraIDRight(cameraID)){
        return core.RM.getCamera(cameraID)->getFOV();
    }
}
float Engine::getCurrentCameraFOV(){
    return core.RM.getCurrentCamera()->getFOV();
}

luabridge::LuaRef Engine::getCameraRotation(int cameraID){
    if(core.RM.isCameraIDRight(cameraID)){
        glm::vec2 rotation = core.RM.getCamera(cameraID)->getRotation();
        float yaw = rotation.x, // Z
              pitch = rotation.y; // Y
        luabridge::LuaRef luaRotate = luabridge::newTable(core.lua.getLuaState());
        luaRotate["yaw"] = yaw;
        luaRotate["pitch"] = pitch;
        return luaRotate;
    }
}
luabridge::LuaRef Engine::getCurrentCameraRotation(){
    glm::vec2 rotation = core.RM.getCurrentCamera()->getRotation();
    float yaw = rotation.x, // Z
          pitch = rotation.y; // Y
    luabridge::LuaRef luaRotate = luabridge::newTable(core.lua.getLuaState());
    luaRotate["yaw"] = yaw;
    luaRotate["pitch"] = pitch;
    return luaRotate;
}

void Engine::setCameraPosition(int cameraID, float X, float Y, float Z){
    if(core.RM.isCameraIDRight(cameraID)){
        core.RM.getCamera(cameraID)->setPosition(X, Y, Z);
    }
}
void Engine::setCurrentCameraPosition(float X, float Y, float Z){
    core.RM.getCurrentCamera()->setPosition(X, Y, Z);
}

void Engine::setCameraSensitivity(int cameraID, float sensitivity){
    if(core.RM.isCameraIDRight(cameraID)){
        core.RM.getCamera(cameraID)->setMouseSensitivity(sensitivity);
    }
}
void Engine::setCurrentCameraSensitivity(float sensitivity){
    core.RM.getCurrentCamera()->setMouseSensitivity(sensitivity);
}

void Engine::setCameraSpeed(int cameraID, float speed){
    if(core.RM.isCameraIDRight(cameraID)){
        core.RM.getCamera(cameraID)->setSpeed(speed);
    }
}
void Engine::setCurrentCameraSpeed(float speed){
    core.RM.getCurrentCamera()->setSpeed(speed);
}

void Engine::setCameraFOV(int cameraID, float FOV){
    if(core.RM.isCameraIDRight(cameraID)){
        core.RM.getCamera(cameraID)->setFOV(FOV);
    }
}
void Engine::setCurrentCameraFOV(float FOV){
    core.RM.getCurrentCamera()->setFOV(FOV);
}

void Engine::setCameraRotation(int cameraID, float yaw, float pitch){
    if(core.RM.isCameraIDRight(cameraID)){
        core.RM.getCamera(cameraID)->setRotation(yaw, pitch);
    }
}
void Engine::setCurrentCameraRotation(float yaw, float pitch){
    core.RM.getCurrentCamera()->setRotation(yaw, pitch);
}

void Engine::setNoiseSeed(int seed){
    noise.SetSeed(seed);
}

void Engine::setNoiseType(int type){
    noise.SetNoiseType(static_cast<FastNoise::NoiseType>(type));
}

void Engine::setNoiseFrequency(float frequency){
    noise.SetFrequency(frequency);
}

void Engine::setCellularDistanceFunction(int function){
    noise.SetCellularDistanceFunction(static_cast<FastNoise::CellularDistanceFunction>(function));
}

void Engine::setCellularJitter(float jitter){
    noise.SetCellularJitter(jitter);
}

void Engine::setCellularReturnType(int returnType){
    noise.SetCellularReturnType(static_cast<FastNoise::CellularReturnType>(returnType));
}

void Engine::setFractalGain(float gain){
    noise.SetFractalGain(gain);
}

void Engine::setFractalLacunarity(float lacunarity){
    noise.SetFractalLacunarity(lacunarity);
}

void Engine::setFractalOctaves(int octaves){
    noise.SetFractalOctaves(octaves);
}

void Engine::setFractalType(int type){
    noise.SetFractalType(static_cast<FastNoise::FractalType>(type));
}

void Engine::setInterp(int interp){
    noise.SetInterp(static_cast<FastNoise::Interp>(interp));
}

float Engine::getNoise(int X, int Z){
    return noise.GetNoise(X, Z);
}

int Engine::createThread(){
    return core.RM.createThread();
}

void Engine::startThread(int threadID){
    core.RM.startThread(threadID);
}

void Engine::setThreadFunction(int threadID, luabridge::LuaRef function){
    core.RM.setThreadFunction(threadID, [function](){function();});
}
