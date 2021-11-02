#pragma once
#include <glad/glad.h>  // Manages function pointers
#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include 

// TODO, DO THIS LOL !! 
class Cube {
private:
    unsigned int vaoID;
    unsigned int vboID;
    GLenum usage = GL_DYNAMIC_DRAW;
    // X Y Z Tx Ty
    // You could also have 2 arrays...
    // TODO: simplify vertices with element buffer
    float[108] vertices;
    float[72] textureCoordinates;
public:
    Cube(Texture& t);
    Cube(float x, float y, float size, Texture& t);
    Cube(float x, float y, float size);
    Cube();
}