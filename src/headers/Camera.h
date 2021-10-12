#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>  // Manages function pointers
#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
private:
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

public: 
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera movement and options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;



}