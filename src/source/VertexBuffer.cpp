#include "VertexBuffer.h"


void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VertexBuffer::bind(GLenum target) {
    glBindBuffer(target, this->VBO);
}
void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

}

// TODO: add easier way to do this eventually...
void VertexBuffer::setBufferData(GLsizeiptr size,
                        const GLvoid* data, GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
void VertexBuffer::setBufferData(GLenum target, GLsizeiptr size,
                        const GLvoid* data, GLenum usage) {
    glBufferData(target, size, data, usage);
}
// Eventually make another class that handles size automatically...
void VertexBuffer::setVertexAttributePointer(GLuint index, GLint size, 
                                            GLenum type, GLboolean normalized, 
                                            GLsizei stride) {
    glVertexAttribPointer(index, size, type, normalized, stride, (void*) 0);
}

// All arguments
void VertexBuffer::setVertexAttributePointer(GLuint index, GLint size, 
                                            GLenum type, GLboolean normalized, 
                                            GLsizei stride, const void* offset) {
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

// Does not include normalized and offset.
void VertexBuffer::setVertexAttributePointer(GLuint index, GLint size, float type,
                                            GLsizei stride) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*) 0);
}

// Enables the attribute at location.
void VertexBuffer::enableAttribArray(unsigned int location) {
    glEnableVertexAttribArray(location);
}
VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &this->VBO);
}


VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &this->VBO);
}


