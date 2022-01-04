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
#include <random>
#include <math.h>
struct Transformation {
    float[16] trans_matrix;
}

class RectangleStack {
private:
    VertexArray vao;       
    // contains positions of vertices
    VertexBuffer verticesBuf; 
    // Single Rectangle: [v1, v2, v3, v4, v5, v6].
    //VertexBuffer positionBuf;
    VertexBuffer colorBuf;
    VertexBuffer posBuf;
    // ssbo
    VertexBuffer tranSSbuf;
    ShaderProgram* sp;
    float* positions;   // [x, y, z]
    float* vertices;    // [6 XYZ coords, 18 floats total per rect]
    float* colors;
    float* trans;       // [16 floats per rect]
    float xWid;
    float yLen;
    int num_rect;
    int points_size;

public:
    RectangleStack(int num_rect, ShaderProgram* sp);
    ~RectangleStack();

    void draw();
    void initialize(float xWidth, float yLength);
    float norm_randf() {return float(rand()) / float(RAND_MAX);}
    float neg_randf() {return float(rand()) / float(RAND_MAX) * 2 - 1;}
    void randomizeLocations();
    void setColor(int rect_idx, float r, float g, float b);
    void setPosition(int rect_idx, float x, float y, float z);
};