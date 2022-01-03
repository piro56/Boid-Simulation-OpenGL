#pragma once
#include <glad\glad.h>

class VertexBuffer {
private:
    unsigned int VBO;
public:
    void bind();
    void bind(GLenum target);
    void unbind();
    void setBufferData(GLsizeiptr size,
                        const GLvoid* data, GLenum usage);
    void setBufferData(GLenum target,GLsizeiptr size,
                        const GLvoid* data, GLenum usage);
    void setVertexAttributePointer(GLuint index, GLint size, GLenum type,
                                   GLboolean normalized, GLsizei stride);
    void setVertexAttributePointer(GLuint index, GLint size, float type, GLsizei stride);
    void setVertexAttributePointer(GLuint index, GLint size, 
                                            GLenum type, GLboolean normalized, 
                                            GLsizei stride, const void* offset);
    void enableAttribArray(unsigned int location);
    unsigned int getBuffer() {return VBO; }
    VertexBuffer();
    ~VertexBuffer();
};