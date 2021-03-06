#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "Core/Core.h"

class Engine {
private:
    static Core core;
public:
    static int createShader(const std::string& vertexShader, const std::string& fragmentShader);

    static int createBlockSystem();

    static void addBlockInfo(int blockSystemID, int X, int Y, int Z);

    static void setBlockTexture(int direction, int blockSystemID, int textureID);

    static void setBlockSystemShader(int blockSystemID, int shaderID);

    static void setCameraToBlockSystem(int cameraID, int blockSystemID);

    static void drawBlocks(int blockSystemID);

    static void clearBlocksData(int blockSystemID);

    static int loadTexture(const std::string& fileName,  bool isOpaque);

    static bool isPressed(int buttonID);

    static void handleCamera(int cameraID, int direction);

    static void handleCurrentCamera(int direction);

    static float getCameraX(int cameraID);

    static float getCameraY(int cameraID);

    static float getCameraZ(int cameraID);

    static float getCurrentCameraX();

    static float getCurrentCameraY();

    static float getCurrentCameraZ();

    static float getCameraFrontX(int cameraID);

    static float getCameraFrontY(int cameraID);

    static float getCameraFrontZ(int cameraID);

    static float getCurrentCameraFrontX();

    static float getCurrentCameraFrontY();

    static float getCurrentCameraFrontZ();

    static float getCameraYaw(int cameraID);

    static float getCameraPitch(int cameraID);

    static float getCurrentCameraYaw();

    static float getCurrentCameraPitch();

    static float getCameraSensitivity(int cameraID);

    static float getCurrentCameraSensitivity();

    static float getCameraSpeed(int cameraID);

    static float getCurrentCameraSpeed();

    static float getCameraFOV(int cameraID);

    static float getCurrentCameraFOV();

    static void setCameraPosition(int cameraID, float X, float Y, float Z);

    static void setCurrentCameraPosition(float X, float Y, float Z);

    static void setCameraSensitivity(int cameraID, float sensitivity);

    static void setCurrentCameraSensitivity(float sensitivity);

    static void setCameraSpeed(int cameraID, float speed);

    static void setCurrentCameraSpeed(float speed);

    static void setCameraFOV(int cameraID, float FOV);

    static void setCurrentCameraFOV(float FOV);

    static void setCameraRotation(int cameraID, float yaw, float pitch);

    static void setCurrentCameraRotation(float yaw, float pitch);

    static void setNoiseSeed(int seed);

    static void setNoiseType(int type);

    static void setNoiseFrequency(float frequency);

    static void setCellularDistanceFunction(int function);

    static void setCellularJitter(float jitter);

    static void setCellularReturnType(int returnType);

    static void setFractalGain(float gain);

    static void setFractalLacunarity(float lacunarity);

    static void setFractalOctaves(int octaves);

    static void setFractalType(int type);

    static void setInterp(int interp);

    static float getNoise(int X, int Z);

    static int createLuaState(const std::string& directory);

    static void addEngineFunctions(LuaState* luaState);

    static void start();
};
