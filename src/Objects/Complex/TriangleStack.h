#pragma once
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include <ElementBuffer.h>
#include "RectangleStack.h" // included for transform data struct

#include <vector>
#include <random>
#include <time.h>
#include <array>
#include <random>
#include <math.h>
class TriangleStack {
private:
    VertexArray vao;       
    // contains positions of vertices
    VertexBuffer verticesBuf; 
    VertexBuffer colorBuf;
    VertexBuffer posBuf;
    // ssbo
    VertexBuffer transformSSB;
    ShaderProgram* sp;
    float* positions;   // [x, y, z]
    float* vertices;    // [6 XYZ coords, 18 floats total per rect]
    float* colors;
    TransformData* trans_data;
    float xWid;
    float yLen;
    int num_tri;
    int points_size;

public:
    TriangleStack(int num_tri, ShaderProgram* sp);
    ~TriangleStack();
    void draw();
    void initialize(float xWidth, float yLength);
    float norm_randf() {return float(rand()) / float(RAND_MAX);}
    float neg_randf() {return float(rand()) / float(RAND_MAX) * 2 - 1;}
    void randomizeLocations();
    void setRotations();
    void setColor(int rect_idx, float r, float g, float b);
    void setPosition(int rect_idx, float x, float y, float z);
    void setRotation(int rect_idx, float angle_radians);
    
};