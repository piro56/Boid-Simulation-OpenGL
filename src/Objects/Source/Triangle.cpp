#include "Triangle.h"

void Triangle::draw() {
    if (tex != nullptr) {
        std::cout << "Enabling texture..\n";
        tex->bindEnable();
    }
    if (shaderProgram != nullptr && useShader) {
        this->preDraw();
    }
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
Triangle::Triangle(float xSize, float ySize, std::string vsrc, std::string fsrc) {
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
    initTriangle(triVertices, triColors, triTexCoords, vsrc, fsrc);
    this->transform = glm::mat4(1.0f);
    //transform = glm::rotate(transform, 0.0f, glm::vec3(0.0, 0.0, 1.0));
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    this->shaderProgram->use();
    this->shaderProgram->setMatrix4f("transform", 1, glm::value_ptr(transform));
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
    this->transform = glm::mat4(1.0f);
    //transform = glm::rotate(transform, 0.0f, glm::vec3(0.0, 0.0, 1.0));
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    this->shaderProgram->use();
    this->shaderProgram->setMatrix4f("transform", 1, glm::value_ptr(transform));
    }
}
void Triangle::initTriangle(float* verticesArr, float* colorsArr, float* texCoordsArr,
                            std::string vsrc, std::string fsrc) {
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
    // set to tex coords not colors
    this->vbo[2].bind();
    this->vbo[2].setBufferData(sizeof(colors), colors, usage);
    this->vbo[2].setVertexAttributePointer(2, 2, GL_FLOAT, 2 * sizeof(float));
    this->vbo[2].enableAttribArray(2);
    if (useShader) {
    ShaderProgram* s = new ShaderProgram(ShaderProgram::get_shader_file(vsrc),
                           ShaderProgram::get_shader_file(fsrc));
    this->shaderProgram = s;
    }
}

// REORDER
// POSITION -> ROTATION -> SCALE UPDATES VALUES (have a boolean check to update in predraw)
// PREDRAW -> PERFORMS TRANSFORMATIONS, SETS UNIFORM

void Triangle::setRotation(float rotation) {
    this->rotation = rotation;
}
void Triangle::preDraw() {
    if (transUpdated){
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    transform = glm::rotate(transform, rotation, glm::vec3(0.0,0.0,1.0));
    transform = glm::scale(transform, glm::vec3(scaleX, scaleY, scaleZ));
    this->shaderProgram->setMatrix4f("transform", GL_FALSE, glm::value_ptr(transform));
    }
    transUpdated = false;
    this->shaderProgram->use();
}
void Triangle::scale(float scaleX, float scaleY, float scaleZ) {
    if (this->scaleX != scaleX || this->scaleY != scaleY || this->scaleZ != scaleZ) {
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        this->scaleZ = scaleZ;
        this->transUpdated = true;
    }
}
void Triangle::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    this->transUpdated = true;
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



