#pragma once
#include "glad\glad.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "ElementBuffer.h"
#include "stb_image.h"
#include <windows.h>

class DVD {
private:
VertexArray vao;
VertexBuffer vbo;
ElementBuffer ebo;
// have to dynamically allocate shader..
ShaderProgram *shader;
unsigned int texture;
float *vertices;
unsigned int *indices;
int offsetX;
int offsetY;
public:
    DVD();
    ~DVD();
};