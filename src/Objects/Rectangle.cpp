#include <Rectangle.h>
using namespace shp;
Rectangle::Rectangle() :
x{0.0f}, y{0.0f}, xLength{0.1f}, yLength{0.1f}
{
    randomColor();
    initializePoints();
}
Rectangle::Rectangle(float xLength, float yLength, float x, float y) 
    : xLength{xLength}, yLength{yLength}, x{x}, y{y}
{
    randomColor();
    initializePoints();
}

Rectangle::Rectangle(float xLength, float yLength) 
    : xLength{xLength}, yLength{yLength}, x{0}, y{0}
{
    randomColor();
    initializePoints();
}

void Rectangle::randomColor() {
    r = (rand() % 255) / 255.0f;
    g = (rand() % 255) / 255.0f;
    b = (rand() % 255) / 255.0f;
    transUpdated = true;
}

void Rectangle::setColor(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::initializePoints() {
    float halfX = xLength / 2.0f;
    float halfY = yLength / 2.0f;
    // we translate this later.
    float vertices[12] = { halfX,  halfY, 0.0f, // TR
                           halfX, -halfY, 0.0f, // BR
                          -halfX, -halfY, 0.0f  // BL 
                          -halfX,  halfX, 0.0f, // TL
                         };
    float colors[12] = {
        r, g, b, r, g, b, r, g, b, r, g, b
    };
    for (int i = 0; i < 12; i++) {
        this->vertices[i] = vertices[i];
        this->colors[i] = colors[i];
    }
    //    float indices[6] = {3, 0, 1, 3, 2, 0};
    this->vao.bind();
    this->vbo[0].bind();
    this->vbo[0].setBufferData(sizeof(this->vertices), this->vertices, usage);
    this->veb.bind();
    this->veb.setData(sizeof(indices), indices, GL_DYNAMIC_DRAW);

    this->vbo[0].setVertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float));
    this->vbo[0].enableAttribArray(0);

    // this->vbo[1].bind();
    // this->vbo[1].setBufferData(sizeof(this->colors), this->colors, usage);
    // this->vbo[1].setVertexAttributePointer(1, 3, GL_FLOAT, 3 * sizeof(float));
    // this->vbo[1].enableAttribArray(1);
}
void Rectangle::scale(float scaleX, float scaleY, float scaleZ) {
    if (this->scaleX != scaleX || this->scaleY != scaleY || this->scaleZ != scaleZ) {
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        this->scaleZ = scaleZ;
        this->transUpdated = true;
    }
}
void Rectangle::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    this->transUpdated = true;
}

void Rectangle::draw() {
    if (shaderProgram != nullptr) {
        this->preDraw();
    }
    veb.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::preDraw() {
    if (transUpdated) {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::rotate(transform, rotation, glm::vec3(0.0,0.0,1.0));
        transform = glm::scale(transform, glm::vec3(scaleX, scaleY, scaleZ));
        this->shaderProgram->setVec3Float("selectedColor", r, g, b);
        this->shaderProgram->setMatrix4f("transform", GL_FALSE, glm::value_ptr(transform));
    }
    transUpdated = false;
    this->shaderProgram->use();
}

void Rectangle::setShader(ShaderProgram* shaderProgram) {
     {
        this->shaderProgram = shaderProgram;
        this->shaderProgram->use();
        preDraw();
    }    
}

void Rectangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->shaderProgram->use();
    this->shaderProgram->setVec3Float("selectedColor", r, g, b);
}