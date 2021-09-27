#include <glad/glad.h>  // Manages function pointers
#include <string>
#include <iostream>

// TODO: Derived classes!!
// Combine Vertex and Fragment into one.


class VertexShader {
private:
    char* shaderData;
    unsigned int vertexShader;
public:
    void compile();
    void loadFromString(std::string shaderCode);
    VertexShader(std::string filepath);
    VertexShader();
};