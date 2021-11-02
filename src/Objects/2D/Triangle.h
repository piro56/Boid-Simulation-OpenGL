#pragma once
#include <glad/glad.h>
#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "ElementBuffer.h"
#include "Texture.h"

class Triangle {

private:
VertexArray vao;
VertexBuffer vbo[3]; // vertices, colors, texCoords
GLenum usage = GL_DYNAMIC_DRAW;
float vertices[9];
float colors[9];
float texCoords[6];
float x = 0.5;
float y = 0.5;
float sizeX;
float sizeY;
public:
    bool useShader = true;
    Texture* tex = nullptr;
    ShaderProgram* shaderProgram = nullptr;
    Triangle();
    Triangle(float* vertices, float* colors, float* texCoords);
    Triangle(float widthRatio, float heightRatio, bool useShader = true);
    ~Triangle();
    void draw();
    void initTriangle(float* vertices, float* colors, float* texCoords);
    void setTexture(Texture& t);    
    void setPosition(float x, float y);
    void setColor(float r, float g, float b);
    inline float getX() {return x;}
    inline float getY() {return y;}
    inline float getSizeX() {return sizeX;}
    inline float getSizeY() {return sizeY;}

};