#pragma once
#include <Triangle.h>

#include <glad/glad.h>
#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"


class Fish: public Triangle {
private:
    float dx = 0.01;
    float dy = 0.01;
    float Ax = 0.0;
    float Ay = 0.0;
public:
    using Triangle::Triangle;
    Fish(float x, float y, float dx, float dy);
    
};