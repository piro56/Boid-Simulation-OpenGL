#include <Rectangle.h>
using namespace shp;
Rectangle::Rectangle() :
x{0.0f}, y{0.0f}, xLength{0.1f}, yLength{0.1f}
{
    randomColor();
}
Rectangle::Rectangle(float xLength, float yLength, float x, float y) 
    : xLength{xLength}, yLength{yLength}, x{x}, y{y}
{
    randomColor();
}

Rectangle::Rectangle(float xLength, float yLength) 
    : xLength{xLength}, yLength{yLength}, x{0}, y{0}
{
    randomColor();
}

void Rectangle::randomColor() {
    r = (rand() % 255) / 255.0f;
    g = (rand() % 255) / 255.0f;
    b = (rand() % 255) / 255.0f;
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
                          -halfX,  halfX, 0.0f, // TL
                          -halfX, -halfY, 0.0f  // BL
                         };
    float colors[12] = {
        r, g, b, r, g, b, r, g, b, r, g, b
    };
    for ( int i = 0; i < 12; i++) {
        this->vertices[i] = vertices[i];
        this->colors[i] = colors[i];
    }
    this->vao.bind();
    this->vbo[0].bind();
    this->vbo[0].setBufferData(sizeof(vertices), vertices, usage);
    this->vbo[0].setVertexAttributePointer(0, 4, GL_FLOAT, 3 * sizeof(float));
    this->vbo[0].enableAttribArray(0);
    this->vbo[1].bind();
    this->vbo[1].setBufferData(sizeof(colors), colors, usage);
    this->vbo[1].setVertexAttributePointer(1, 4, GL_FLOAT, 3 * sizeof(float));
    this->vbo[1].enableAttribArray(1);
    float indices[6] = {3, 0, 1, 3, 2, 0};
    this->veb.bind();
    this->veb.setData(sizeof(indices), indices, GL_DYNAMIC_DRAW);
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
    vao.bind();
    veb.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::preDraw() {
    if (transUpdated) {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::rotate(transform, rotation, glm::vec3(0.0,0.0,1.0));
        transform = glm::scale(transform, glm::vec3(scaleX, scaleY, scaleZ));
            this->shaderProgram->setMatrix4f("transform", GL_FALSE, glm::value_ptr(transform));
    }
    transUpdated = false;
    this->shaderProgram->use();
}