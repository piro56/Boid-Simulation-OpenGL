#pragma once
#include <glad/glad.h>
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
public:
    Texture* tex;
    ShaderProgram* shaderProgram;
    Triangle();
    Triangle(float* vertices, float* colors, float* texCoords);
    Triangle(float x, float y, float size);
    //~Triangle();
    void draw();

    void initTriangle(float* vertices, float* colors, float* texCoords);
    void setTexture(Texture& t);
    void setShader(ShaderProgram& s);
    
};