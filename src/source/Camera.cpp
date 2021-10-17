#include "Camera.h"

    // constructor with vectors
Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
               float yaw = YAW, float pitch = PITCH) 
               : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

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



glm::mat4 Camera::getViewMatrix() {
    // Position = Location of Camera
    // Position + Front = Where Camera is looking i.e. / + \ = |
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw) * cos(glm::radians(Pitch)));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw) * cos(glm::radians(Pitch)));
    this->Front = glm::normalize(front);
    // recalculate Right and Up vector
    this->Right = glm::normalize(glm::cross(Front, WorldUp));
    this->Up = glm::cross(Right, Front);
}

void Camera::ProcessMouseMovement(float xOff, float yOff, GLboolean constrainPitch = true) {
    xOff *= MouseSensitivity;
    yOff *= MouseSensitivity;
    Yaw += xOff;
    Pitch += yOff;
    
    // if we dont want the user to be able to look so far up that they look upside down...
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }
    // update camera vectors with new pitch/yaw
    updateCameraVectors;
}
