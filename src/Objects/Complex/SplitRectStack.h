#pragma once
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include <ElementBuffer.h>
#include "RectangleStack.h"
#include <vector>
#include <random>
#include <time.h>
#include <array>
#include <random>
#include <math.h>
struct BOID {
    float xyzw[4];   // extra for padding std430
    float velocity[3];
    float rotation;
}
class SplitRectStack {
private:
    std::vector<BOID>* boids_vec;   // instance depending on num of segments
    VertexArray vao;       
    // contains positions of base vertices
    VertexBuffer verticesBuf; 
    VertexBuffer posBuf;
    // ssbo
    VertexBuffer transformSSB;
    ShaderProgram* sp;
    float* positions;   // [position offsets]
    float* vertices;    // [XYZ coords]
    float* colors;
    TransformData* trans_data;
    float xWid;
    float yLen;
    int num_shape;
    int points_size;

public:
    SplitRectStack(int num_shape, ShaderProgram* sp);
    ~SplitRectStack();
    void draw();
    void initialize(float xWidth, float yLength);
    float norm_randf() {return float(rand()) / float(RAND_MAX);}
    float neg_randf() {return float(rand()) / float(RAND_MAX) * 2 - 1;}
    void randomizeLocations();
    void setRotations();
    void setColor(int shapeidx, float r, float g, float b);
    void setPosition(int shapeidx, float x, float y, float z);
    void setRotation(int shapeidx, float angle_radians);
    

};