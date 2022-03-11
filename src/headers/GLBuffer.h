#pragma once
#include <glad\glad.h>

class GLBuffer {
private:
    // OpenGL buffer object
    unsigned int GLBO;
    GLenum target;

public:
    void bind();
    void unbind();
    void setBufferData(GLsizeiptr size,
                        const GLvoid* data, GLenum usage);
    void setVertexAttributePointer(GLuint index, GLint size, GLenum type,
                                   GLboolean normalized, GLsizei stride);
    void setVertexAttributePointer(GLuint index, GLint size, float type, GLsizei stride);
    void setVertexAttributePointer(GLuint index, GLint size, 
                                            GLenum type, GLboolean normalized, 
                                            GLsizei stride, const void* offset);
    void enableAttribArray(unsigned int location);
    unsigned int getBuffer() { return GLBO; }
    GLenum getTarget() { return target; }
    GLBuffer(GLenum target);
    ~GLBuffer();
};