#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window
#include <string>
#include <iostream>

// TODO: Derived classes!!

class FragmentShader {
private:
    char* shaderData;
    unsigned int fragShader;
public:
    void compile();
    void loadFromString(std::string shaderCode);
    FragmentShader(std::string filepath);
    FragmentShader();
};