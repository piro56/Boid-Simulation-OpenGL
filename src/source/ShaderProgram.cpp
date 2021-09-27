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
    // TODO: FIll this char* in!
    char* vertexShaderSource = new char();
    char* fragShaderSource = new char();

    glShaderSource(this->vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(this->vertexShader, 1, &fragShaderSource, NULL);
    
    // COMPILE AND ATTACH...


    // Cleanup dynamically allocated characters.
    delete[] vertexShaderSource;
    delete[] fragShaderSource;
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);

}