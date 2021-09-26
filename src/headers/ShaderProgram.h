#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window
#include <string>
#include <iostream>

// TODO: Derived classes!!
// Combine Vertex and Fragment into one.


class ShaderProgram {
private:
    char* shaderData;
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    bool loaded;
public:
    // Detach shader and recompile program?
    //void loadVertexShader(std::string vertexShader);
    //void loadFragmentShader(std::string fragShader);
    
    // Compile shaders and link
    void loadShaders(std::string vertexShaderPath, std::string fragShaderPath);
    void compileCheck(unsigned int vertexShader, bool vertex);
    void use();
    ShaderProgram(std::string vertexShaderPath, std::string fragShaderPath);
    ShaderProgram();
    
};