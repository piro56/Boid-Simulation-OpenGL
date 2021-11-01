#include "Triangle.h"

void Triangle::draw() {
    if (tex != nullptr) {
        tex->bindEnable();
    }
    if (shaderProgram != nullptr) {
        shaderProgram->use();
    }
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::Triangle(float x, float y, float size) {
    float sizeHalf = size / 2;
    float triVertices[9] = {
        x - sizeHalf, y - sizeHalf, 0.0f,
        x + sizeHalf, y - sizeHalf, 0.0f,
        x, y + sizeHalf, 0.0f 
    };
    float triColors[9] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    float triTexCoords[6] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };
    initTriangle(triVertices, triColors, triTexCoords);
}
void Triangle::initTriangle(float* verticesArr, float* colorsArr, float* texCoordsArr) {
    if (sizeof(vertices) / sizeof(float) != 9) {
        std::cout << "OBJECT::TRIANGLE::INVALID_VERTICES_SIZE\n";
    }
    if (sizeof(colors) / sizeof(float) != 9) {
        std::cout << "OBJECT::TRIANGLE::INVALID_COLOR_SIZE\n";

    }
    if (sizeof(texCoords) / sizeof(float) != 6) {

    }        std::cout << "OBJECT::TRIANGLE::INVALID_TEXCOORD_SIZE\n";

    for ( int i = 0; i < 9; i++) {
        this->vertices[i] = verticesArr[i];
        this->colors[i] = colorsArr[i];
    }
    for (int i = 0; i < 6; i++) {
        this->texCoords[i] = texCoordsArr[i];
    }
    // initialize VAO and VBO
    this->vao.bind();
    this->vbo[0].bind();
    this->vbo[0].setBufferData(sizeof(vertices), vertices, usage);
    this->vbo[0].setVertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float));
    this->vbo[0].enableAttribArray(0);
    this->vbo[1].bind();
    this->vbo[1].setBufferData(sizeof(colors), colors, usage);
    this->vbo[1].setVertexAttributePointer(1, 3, GL_FLOAT, 3 * sizeof(float));
    this->vbo[0].enableAttribArray(1);
    this->vbo[2].bind();
    this->vbo[2].setBufferData(sizeof(colors), colors, usage);
    this->vbo[2].setVertexAttributePointer(2, 2, GL_FLOAT, 2 * sizeof(float));
    this->vbo[0].enableAttribArray(2);

}

void Triangle::setTexture(Texture& t) {
    this->tex = &t;
}

void Triangle::setShader(ShaderProgram& s) {
    this->shaderProgram = &s;
}

