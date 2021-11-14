#pragma once
#define _USE_MATH_DEFINES
#include <Triangle.h>

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <memory>
#include <set>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"


struct FishSettings {
    float FOLLOW_STRENGTH = 0.0005f;
    float CENTERING_RANGE = 0.01f;
    float CENTERING_STRENGTH = 0.000005;
    float AVOID_WALL_STRENGTH = 0.00002;
    float AVOID_DIST_THRESHOLD = 0.04; 
    float AVOID_STRENGTH = 0.0005;
    float MAX_SPEED = 0.001; 
    float MIN_SPEED = 0.000375; 
    float SIZE = 1.0;
};

class Fish: public Triangle {
private:
    constexpr static float FOLLOW_STRENGTH = 0.0005f;
    constexpr static float CENTERING_RANGE = 0.01f;
    constexpr static float CENTERING_STRENGTH = 0.000005;
    constexpr static float AVOID_WALL_STRENGTH = 0.00002;
    constexpr static float AVOID_DIST_THRESHOLD = 0.04; 
    constexpr static float AVOID_STRENGTH = 0.0005;
    constexpr static float MAX_SPEED = 0.001; 
    constexpr static float MIN_SPEED = 0.000375;
    std::vector<std::unique_ptr<std::set<Fish*>>>* segmentedFish;
    int vectorPosition = -1;
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
    static FishSettings& FISH_SETTINGS;
    Fish(float x, float y, float dx, float dy, std::vector<Fish*>* otherFish, 
            std::vector<std::unique_ptr<std::set<Fish*>>>* segmentedFish);
    Fish(float xSize, float ySize, std::vector<Fish*>* otherFishes);
    void processMovement();
    void setPosition(float x, float y);
    void updateSegment();
    void draw();
    static float angleBetween(float x1, float y1, float x2, float y2) {
        float dot = x1*x2 + y1*y2;
        float det = x1*y2 - y1*x2;
        return atan2f(det, dot);
    }

};