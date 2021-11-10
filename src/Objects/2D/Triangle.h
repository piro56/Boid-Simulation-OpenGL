#pragma once
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "ElementBuffer.h"
#include "Texture.h"

class Triangle {

protected:
VertexArray vao;
VertexBuffer vbo[3]; // vertices, colors, texCoords
GLenum usage = GL_DYNAMIC_DRAW;
float vertices[9];
float colors[9];
float texCoords[6];
float x = 0.5;
float y = 0.5;
float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;
float sizeX;
float sizeY;
float rotation = 0.0f;
bool transUpdated = true;
glm::mat4 transform;
public:
    bool useShader = true;
    Texture* tex = nullptr;
    ShaderProgram* shaderProgram = nullptr;
    Triangle();
    Triangle(float* vertices, float* colors, float* texCoords);
    Triangle(float xSize, float ySize, std::string vsrc, std::string fsrc);
    Triangle(float widthRatio, float heightRatio, bool useShader = true);
    ~Triangle();
    void draw();
    void initTriangle(float* vertices, float* colors, float* texCoords,
                     std::string vsrc = "vertex\\triangle.vs", 
                     std::string fsrc = "fragment\\triangle.fs");
    void setTexture(Texture& t);    
    void setPosition(float x, float y);
    void setColor(float r, float g, float b);
    void setRotation(float rotation);
    void scale(float scaleX, float scaleY, float scaleZ);

    void preDraw();

    inline float getX() {return x;}
    inline float getY() {return y;}
    inline float getSizeX() {return sizeX;}
    inline float getSizeY() {return sizeY;}

};