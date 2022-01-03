#pragma once
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include <ElementBuffer.h>

#include <vector>
#include <random>
#include <time.h>
#include <array>

class RectangleStack {
private:
    VertexArray vao;       
    VertexBuffer verticesBuf;
    VertexBuffer positionBuf;
    VertexBuffer colorBuf;;
    float* vertices;
    int num_rect;

public:
    ~RectangleStack();
}