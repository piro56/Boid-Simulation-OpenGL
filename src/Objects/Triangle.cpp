#include "Triangle.h"

void Triangle::draw() {
    if (tex != nullptr) {
        std::cout << "Enabling texture..\n";
        tex->bindEnable();
    }
    if (shaderProgram != nullptr && useShader) {
        shaderProgram->use();
    }
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::Triangle(float xSize, float ySize, bool useShader) {
    this->x = 0.0f;
    this->y = 0.0f;
    this->sizeX = xSize;
    this->sizeY = ySize;
    float halfX = xSize / 2.0f;
    float halfY = ySize / 2.0f;
    float triVertices[9] = {
        -halfX, -halfY, 0.0f,
        halfX, -halfY, 0.0f,
        0.0f, halfY, 0.0f
    };
    float triColors[9] = {
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    float triTexCoords[6] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };
    initTriangle(triVertices, triColors, triTexCoords);
    if (useShader) {
    this->shaderProgram->use();
    this->shaderProgram->setVec2Float("ourPosition", x, y);
    }
}
void Triangle::initTriangle(float* verticesArr, float* colorsArr, float* texCoordsArr) {
    if (sizeof(vertices) / sizeof(float) != 9) {
        std::cout << "OBJECT::TRIANGLE::INVALID_VERTICES_SIZE\n";
    }
    if (sizeof(colors) / sizeof(float) != 9) {
        std::cout << "OBJECT::TRIANGLE::INVALID_COLOR_SIZE\n";

    }
    if (sizeof(texCoords) / sizeof(float) != 6) {
        std::cout << "OBJECT::TRIANGLE::INVALID_TEXCOORD_SIZE\n";
    }        

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
    this->vbo[1].enableAttribArray(1);
    this->vbo[2].bind();
    this->vbo[2].setBufferData(sizeof(colors), colors, usage);
    this->vbo[2].setVertexAttributePointer(2, 2, GL_FLOAT, 2 * sizeof(float));
    this->vbo[2].enableAttribArray(2);
    if (useShader) {
    ShaderProgram* s = new ShaderProgram(ShaderProgram::get_shader_file("vertex\\triangle.vs"),
                           ShaderProgram::get_shader_file("fragment\\triangle.fs"));
    this->shaderProgram = s;
    }
}
void Triangle::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    this->shaderProgram->use();
    this->shaderProgram->setVec2Float("ourPosition", x, y);
}
void Triangle::setTexture(Texture& t) {
    this->tex = &t;
}
void Triangle::setColor(float r, float g, float b) {
    this->shaderProgram->use();
    this->shaderProgram->setVec3Float("selectedColor", r, g, b);
}


Triangle::~Triangle() {
    if (this->shaderProgram != nullptr && useShader) {
        delete this->shaderProgram;
    }
}



