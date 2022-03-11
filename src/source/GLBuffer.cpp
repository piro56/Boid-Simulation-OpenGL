#include "GLBuffer.h"
    
GLBuffer::GLBuffer(GLenum target) {
    this->target = target;
    glGenBuffers(1, &this->GLBO);
}

GLBuffer::~GLBuffer() {
    glDeleteBuffers(1, &this->GLBO);
}
void GLBuffer::bind() {
    glBindBuffer(this->target, this->GLBO);
}
void GLBuffer::unbind() {
    glBindBuffer(this->target, 0);
}

void GLBuffer::setBufferData(GLsizeiptr size,
                    const GLvoid* data, GLenum usage) {
    glBufferData(target, size, data, usage);
}


void GLBuffer::setVertexAttributePointer(GLuint index, GLint size, GLenum type,
                                GLboolean normalized, GLsizei stride) {
    glVertexAttribPointer(index, size, type, normalized, stride, (void*) 0);

}
// All arguments
void GLBuffer::setVertexAttributePointer(GLuint index, GLint size, 
                                            GLenum type, GLboolean normalized, 
                                            GLsizei stride, const void* offset) {
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

// Does not include normalized and offset.
void GLBuffer::setVertexAttributePointer(GLuint index, GLint size, float type,
                                            GLsizei stride) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*) 0);
}
void GLBuffer::enableAttribArray(unsigned int location) {
    glEnableVertexAttribArray(location);
}