#include <glad\glad.h>
#include <GLFW\include\glfw3.h>

class VertexBuffer {
    void bind();
    void unbind();
    void setBufferData();
    void setVertexAttributePointer(GLuint index, GLint size, GLenum type,
                                   GLboolean normalized, GLsizei stride);
    void enableAttribArray(unsigned int location);
    VertexBuffer();
    ~VertexBuffer();
};