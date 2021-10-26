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
    static constexpr float YAW = -90.0f;
    static constexpr float PITCH = 0.0f;
    static constexpr float SPEED =  2.5f;
    static constexpr float SENSITIVITY = 0.1f;
    static constexpr float ZOOM = 45.0f;

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


    // Constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
               float yaw = YAW, float pitch = PITCH) 
               : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    };
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    
    // Functions
    glm::mat4 getViewMatrix(); 

    void ProcessMouseMovement(float xOff, float yOff, GLboolean constrainPitch);
    void ProcessKeyboardMovement(Camera_Movement direction, float deltaTime);
    void ProcessMouseScroll(float yOff);
private:
    void updateCameraVectors();
};