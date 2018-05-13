#include "Camera.h"

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(CAMERA_SPEED), MouseSensitivity(CAMERA_SENSITIVITY), FOV(CAMERA_FOV) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(CAMERA_SPEED), MouseSensitivity(CAMERA_SENSITIVITY), FOV(CAMERA_FOV) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(int direction) {
    float velocity = MovementSpeed;
    if (direction == CAMERA_FORWARD)
        Position += Front * velocity;
    if (direction == CAMERA_BACKWARD)
        Position -= Front * velocity;
    if (direction == CAMERA_LEFT)
        Position -= Right * velocity;
    if (direction == CAMERA_RIGHT)
        Position += Right * velocity;
    if (direction == CAMERA_UP)
        Position += Up * velocity;
    if (direction == CAMERA_DOWN)
        Position -= Up * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
    if (FOV >= 1.0f && FOV <= CAMERA_FOV)
        FOV -= yoffset;
    if (FOV <= 1.0f)
        FOV = 1.0f;
    if (FOV >= CAMERA_FOV)
        FOV = CAMERA_FOV;
}

void Camera::setPosition(float X, float Y, float Z){
    Position.x = X;
    Position.y = Y;
    Position.z = Z;
}

glm::vec3 Camera::getPosition(){
    return Position;
}

glm::vec3 Camera::getFront(){
    return Front;
}

void Camera::setRotation(float yaw, float pitch){
    Yaw = yaw;
    Pitch = pitch;
}

glm::vec2 Camera::getRotation(){
    glm::vec2 rotation;
    rotation.x = Yaw;
    rotation.y = Pitch;
    return rotation;
}

void Camera::setSpeed(float speed){
    MovementSpeed = speed;
}

float Camera::getSpeed(){
    return MovementSpeed;
}

void Camera::setMouseSensitivity(float sensitivity){
    MouseSensitivity = sensitivity;
}

float Camera::getMouseSensitivity(){
    return MouseSensitivity;
}

void Camera::setFOV(float FOV){
    this->FOV = FOV;
}

float Camera::getFOV(){
    return FOV;
}
