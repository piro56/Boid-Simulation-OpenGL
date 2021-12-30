#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <vector>
#include <random>
#include <time.h>

#define M_PI 3.14159265358979323846
#define DEFAULT_CIRCLE_SEGMENTS 10
class Circle {
private:
    float x;
    float y;
    float radius;
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int numSegments;
    void initializePoints();
    // REMEMBER: ADD x + pt, y + pt
    std::vector<std::pair<float, float>> pts;
    //(x + (radius * cos(i * twicePi / 20))),
    //(y + (radius * sin(i * twicePi / 20)))
public:
    Circle();
    Circle(int radius, int x, int y);
    void setColor(int r, int g, int b);
    void randomColor();
    
};