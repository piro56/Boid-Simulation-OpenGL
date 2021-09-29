#include <ElementBuffer.h>

// Perhaps move this in as a subclass into a VBO...

ElementBuffer::ElementBuffer() {
    glGenBuffers(1, &this->ID);
}

void ElementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void ElementBuffer::setData(GLsizeiptr size, const void* data, GLenum usage) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}
ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &this->ID);
}


