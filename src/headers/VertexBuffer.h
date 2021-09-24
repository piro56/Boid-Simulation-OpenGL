#include <glad\glad.h>
#include <glfw3.h>

class VertexBuffer {
private:
    unsigned int VBO;
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
    VertexBuffer();
    ~VertexBuffer();
};