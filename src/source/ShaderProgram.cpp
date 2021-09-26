#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexShader, std::string fragShader) {
    ShaderProgram();
    this->loadShaders(vertexShader, fragShader);
}

ShaderProgram::ShaderProgram() {
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}


void ShaderProgram::use() {
    glUseProgram(this->shaderProgram);
}


void ShaderProgram::loadShaders(std::string vertexShaderPath, std::string fragShaderPath) {
    // LOAD CHAR*
    if(this->loaded) {
        std::cout << "WARN::SHADER -- Already Loaded!\n";
        return;
    }
    
    // specify size of Source and place it in the source
    char* vertexShaderSource = new char();
    char* fragShaderSource = new char();

    glShaderSource(this->vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(this->vertexShader, 1, &fragShaderSource, NULL);
    
    // COMPILE
    glCompileShader(this->vertexShader);
    compileCheck(this->vertexShader);
    glCompileShader(this->fragmentShader);
    compileCheck(this->fragmentShader);

    // ATTACH
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
    
    // Cleanup dynamically allocated characters.
    delete[] vertexShaderSource;
    delete[] fragShaderSource;
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);

}

void ShaderProgram::compileCheck(unsigned int shader, bool vertex) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        if(vertex) {
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
    }
}