#include <glad\glad.h>
#include <glfw3.h>

class VertexArray {
private:
    unsigned int VAO;
public:
    VertexArray();
    void bind();
    void unbind();
    ~VertexArray();
};