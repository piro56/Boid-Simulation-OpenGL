#include <glad\glad.h>

class ElementBuffer {
private:
unsigned int ID;
public:
    ElementBuffer();
    void bind();
    void setData(GLsizeiptr size, const void* data, GLenum usage);
    inline unsigned int getID() { return ID; } 
    ~ElementBuffer();
};