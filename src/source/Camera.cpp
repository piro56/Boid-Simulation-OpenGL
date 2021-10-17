#include "Camera.h"

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    this->Front = glm::vec3(0.0f, 0.0f, 1.0f);
    this->MovementSpeed = Camera::SPEED;
    MouseSensitivity = Camera::SENSITIVITY;
    this->Zoom = Camera::ZOOM;
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
}

