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
#define M_PI 3.14159265358979323846
#define DEFAULT_CIRCLE_SEGMENTS 10
namespace shp {
class Rectangle {
private:
    // DRAWING:
    VertexArray vao;
    VertexBuffer vbo[4];
    ElementBuffer veb;
    ShaderProgram* shaderProgram;
    GLenum usage = GL_DYNAMIC_DRAW;
    float vertices[12];
    float colors[12];
    float texCoords[8];
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float scaleZ = 1.0f;
    float rotation = 0.0f;
    bool transUpdated = true;
    glm::mat4 transform;

    float x;
    float y;
    float xLength;
    float yLength;
    float r, g, b;
    void initializePoints();

public:
    Rectangle();
    Rectangle(float xLength, float yLength, float x, float y);
    Rectangle(float xLength, float yLength);
    void setColor(int r, int g, int b);
    void randomColor();
    void setShader(ShaderProgram* sp) {
        this->shaderProgram = sp;
    }
    void preDraw();
    void draw();
    void scale(float scaleX, float scaleY, float scaleZ);
    void setPosition(float x, float y);


};
}