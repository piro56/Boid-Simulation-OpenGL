#pragma once
#define _USE_MATH_DEFINES
#include <Triangle.h>

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"


class Fish: public Triangle {
private:
    constexpr static float FOLLOW_STRENGTH = 0.005f;

    constexpr static float CENTERING_RANGE = 0.02f;
    constexpr static float CENTERING_STRENGTH = 0.000005;
    constexpr static float AVOID_WALL_STRENGTH = 0.0002;
    constexpr static float AVOID_DIST_THRESHOLD = 0.04; 
    constexpr static float AVOID_STRENGTH = 0.0003;
    constexpr static float MAX_SPEED = 0.001; 
    constexpr static float MIN_SPEED = 0.000375;

    float dx = 0.01;
    float dy = 0.01;
    float Ax = 0.0;
    float Ay = 0.0;
    std::vector<Fish*>* otherFishes;
    void avoidWall(float x, float y);
    void limitSpeed();
    void calculateAvoidance();
    void calculateCentering();
public:
    using Triangle::Triangle;
    Fish(float x, float y, float dx, float dy, std::vector<Fish*>* otherFishes);
    Fish(float xSize, float ySize, std::vector<Fish*>* otherFishes);
    void processMovement();
    void setPosition(float x, float y);
    void draw();
    static float angleBetween(float x1, float y1, float x2, float y2) {
        float dot = x1*x2 + y1*y2;
        float det = x1*y2 - y1*x2;
        return atan2f(det, dot);
    }

};