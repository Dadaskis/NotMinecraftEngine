#include "Engine.h"
#include "Core/Resources/Texture/TextureUtilities.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <thread>

Core Engine::core;

void Engine::start(){
    //std::string title = core.lua.getGlobalString(mainState, "WINDOW_TITLE");
    //int width = core.lua.getGlobalInt(mainState, "WINDOW_WIDTH"),
    //    height = core.lua.getGlobalInt(mainState, "WINDOW_HEIGHT");

    core.window.setCamera(core.RM.getCurrentCamera());
    core.window.createWindow("NotMinecraftEngine", 800, 600);
    int mainState = createLuaState("gamedata\\MainLuaState");
    core.window.start();
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

float Engine::getCameraX(int cameraID){
    return core.RM.getCamera(cameraID)->getPosition().x;
}

float Engine::getCameraY(int cameraID){
    return core.RM.getCamera(cameraID)->getPosition().y;
}

float Engine::getCameraZ(int cameraID){
    return core.RM.getCamera(cameraID)->getPosition().z;
}

float Engine::getCurrentCameraX(){
    return core.RM.getCurrentCamera()->getPosition().x;
}

float Engine::getCurrentCameraY(){
    return core.RM.getCurrentCamera()->getPosition().y;
}

float Engine::getCurrentCameraZ(){
    return core.RM.getCurrentCamera()->getPosition().z;
}

float Engine::getCameraFrontX(int cameraID){
    return core.RM.getCamera(cameraID)->getFront().x;
}

float Engine::getCameraFrontY(int cameraID){
    return core.RM.getCamera(cameraID)->getFront().y;
}

float Engine::getCameraFrontZ(int cameraID){
    return core.RM.getCamera(cameraID)->getFront().z;
}

float Engine::getCurrentCameraFrontX(){
    return core.RM.getCurrentCamera()->getFront().x;
}

float Engine::getCurrentCameraFrontY(){
    return core.RM.getCurrentCamera()->getFront().y;
}

float Engine::getCurrentCameraFrontZ(){
    return core.RM.getCurrentCamera()->getFront().z;
}

float Engine::getCameraYaw(int cameraID){
    return core.RM.getCamera(cameraID)->getRotation().x;
}

float Engine::getCameraPitch(int cameraID){
    return core.RM.getCamera(cameraID)->getRotation().y;
}

float Engine::getCurrentCameraYaw(){
    return core.RM.getCurrentCamera()->getRotation().x;
}

float Engine::getCurrentCameraPitch(){
    return core.RM.getCurrentCamera()->getRotation().y;
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
    core.noise.SetSeed(seed);
}

void Engine::setNoiseType(int type){
    core.noise.SetNoiseType(static_cast<FastNoise::NoiseType>(type));
}

void Engine::setNoiseFrequency(float frequency){
    core.noise.SetFrequency(frequency);
}

void Engine::setCellularDistanceFunction(int function){
    core.noise.SetCellularDistanceFunction(static_cast<FastNoise::CellularDistanceFunction>(function));
}

void Engine::setCellularJitter(float jitter){
    core.noise.SetCellularJitter(jitter);
}

void Engine::setCellularReturnType(int returnType){
    core.noise.SetCellularReturnType(static_cast<FastNoise::CellularReturnType>(returnType));
}

void Engine::setFractalGain(float gain){
    core.noise.SetFractalGain(gain);
}

void Engine::setFractalLacunarity(float lacunarity){
    core.noise.SetFractalLacunarity(lacunarity);
}

void Engine::setFractalOctaves(int octaves){
    core.noise.SetFractalOctaves(octaves);
}

void Engine::setFractalType(int type){
    core.noise.SetFractalType(static_cast<FastNoise::FractalType>(type));
}

void Engine::setInterp(int interp){
    core.noise.SetInterp(static_cast<FastNoise::Interp>(interp));
}

float Engine::getNoise(int X, int Z){
    return core.noise.GetNoise(X, Z);
}

int Engine::createLuaState(const std::string& directory){
    int stateID = core.lua.createState(addEngineFunctions, directory);

    return stateID;
}

void Engine::addEngineFunctions(LuaState* luaState){
    luabridge::getGlobalNamespace(luaState->state)
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
            .addFunction("getCameraX", getCameraX)
            .addFunction("getCameraY", getCameraY)
            .addFunction("getCameraZ", getCameraZ)
            .addFunction("getCurrentCameraX", getCurrentCameraX)
            .addFunction("getCurrentCameraY", getCurrentCameraY)
            .addFunction("getCurrentCameraZ", getCurrentCameraZ)
            .addFunction("getCameraFrontX", getCameraFrontX)
            .addFunction("getCameraFrontY", getCameraFrontY)
            .addFunction("getCameraFrontZ", getCameraFrontZ)
            .addFunction("getCurrentCameraFrontX", getCurrentCameraFrontX)
            .addFunction("getCurrentCameraFrontY", getCurrentCameraFrontY)
            .addFunction("getCurrentCameraFrontZ", getCurrentCameraFrontZ)
            .addFunction("getCameraSensitivity", getCameraSensitivity)
            .addFunction("getCurrentCameraSensitivity", getCurrentCameraSensitivity)
            .addFunction("getCameraSpeed", getCameraSpeed)
            .addFunction("getCurrentCameraSpeed", getCurrentCameraSpeed)
            .addFunction("getCameraFOV", getCameraFOV)
            .addFunction("getCurrentCameraFOV", getCurrentCameraFOV)
            .addFunction("getCameraYaw", getCameraYaw)
            .addFunction("getCameraPitch", getCameraPitch)
            .addFunction("getCurrentCameraYaw", getCurrentCameraYaw)
            .addFunction("getCurrentCameraPitch", getCurrentCameraPitch)
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
            .addFunction("createLuaState", createLuaState)
        .endNamespace();
}
