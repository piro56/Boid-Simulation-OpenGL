#pragma once
#include <glad/glad.h>  // Manages function pointers
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
// TODO: Derived classes!!
// Combine Vertex and Fragment into one.


class ShaderProgram {
private:
    char* shaderData;
    unsigned int shaderProgramID;
    bool loaded;
public:
    // Detach shader and recompile program?
    //void loadVertexShader(std::string vertexShader);
    //void loadFragmentShader(std::string fragShader);
    
    // Compile shaders and link
    //void loadShaders(std::string vertexShaderPath, std::string fragShaderPath);
    void compileCheck(unsigned int vertexShader, bool vertex);
    void use();
    void load(const char* vertexPath, const char* fragPath);
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2Float(const std::string &name, float value_one, float value_two) const;
    void setVec4Float(const std::string &name, float value_one, float value_two, float value_three, float value_four) const;
    ShaderProgram(std::string vertexShaderPath, std::string fragShaderPath);
    ShaderProgram(const char* vertexPath, const char* fragPath);
    ShaderProgram();
    
};