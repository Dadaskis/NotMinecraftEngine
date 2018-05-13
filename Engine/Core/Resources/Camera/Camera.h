#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    CAMERA_FORWARD,
    CAMERA_BACKWARD,
    CAMERA_LEFT,
    CAMERA_RIGHT,
    CAMERA_UP,
    CAMERA_DOWN
};

// Default camera values
constexpr float CAMERA_YAW         = -90.0f;
constexpr float CAMERA_PITCH       =  0.0f;
constexpr float CAMERA_SPEED       =  20.0f;
constexpr float CAMERA_SENSITIVITY =  0.1f;
constexpr float CAMERA_FOV         =  360.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
private:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed = 1.0f;
    float MouseSensitivity;
    float FOV;

    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
public:
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH);
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 getViewMatrix();

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(int direction);

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void processMouseScroll(float yoffset);

    void setPosition(float X, float Y, float Z);
    glm::vec3 getPosition();

    glm::vec3 getFront();

    void setRotation(float yaw, float pitch);
    glm::vec2 getRotation();

    void setSpeed(float speed);
    float getSpeed();

    void setMouseSensitivity(float sensitivity);
    float getMouseSensitivity();

    void setFOV(float FOV);
    float getFOV();
};
