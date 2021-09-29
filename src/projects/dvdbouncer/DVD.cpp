#include "DVD.h"

DVD::DVD() {
    // bind buffers
    this->vao.bind();
    this->vbo.bind();
    this->ebo.bind();
    // load data
    this->vertices = new float[32] {
    // positions          // colors           // texture coords
     0.25f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.25f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.25f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.25f,  0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    this->indices = new unsigned int[6] {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };

    ebo.setData(sizeof(this->indices), indices, GL_STATIC_DRAW);
    vbo.setBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    vbo.setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    vbo.enableAttribArray(0);
    // color attribute
    vbo.setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo.enableAttribArray(1);
    // texture coordinates...
    vbo.setVertexAttributePointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vbo.enableAttribArray(2);

    // Generate Textures... wait for Utils and Textures class!
    // Maybe try and make one bigger include file

}

DVD::~DVD() {
    // clean up dynamic memory!
    delete[] this->vertices;
    delete[] this->indices;
}