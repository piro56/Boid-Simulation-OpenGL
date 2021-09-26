#include "ShaderProgram.h"

//ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath) {
//    ShaderProgram(vertexPath.c_str(), fragmentPath.c_str());
//}

// Inspired by LearnOpenGL.com
ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragPath) {
    unsigned int vertexShader;
    unsigned int fragmentShader;
    std::string vertexCode;
    std::string fragCode;
    std::ifstream vShaderFile;  
    std::ifstream fShaderFile;
    // Ensure ifstream can throw exceptions
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    vShaderFile = std::ifstream(vertexPath);
    fShaderFile = std::ifstream(fragPath);
    if(vShaderFile.is_open() && fShaderFile.is_open()) {
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    } else {
        std::cout << "ERROR::SHADERPROGRAM::FILE_READ_ERROR......" << std::endl;
    }



/*     try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragCode);
        std::stringstream vShaderStream, fShaderStream;
        // read file buffer into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close files
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADERPROGRAM::FILE_READ_ERROR..." << std::endl;
    } */

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    
    // COMPILE
    glCompileShader(vertexShader);
    compileCheck(vertexShader, true);
    glCompileShader(fragmentShader);
    compileCheck(fragmentShader, false);

    // GENERATE PROGRAM
    this->shaderProgramID = glCreateProgram();
    // ATTACH
    glAttachShader(this->shaderProgramID, vertexShader);
    glAttachShader(this->shaderProgramID, fragmentShader);
    glLinkProgram(this->shaderProgramID);
    // Check Program Link Errors
    int success;
    char infoLog[512];
    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILURE\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}



void ShaderProgram::use() {
    glUseProgram(this->shaderProgramID);
}


//void ShaderProgram::loadShaders(std::string vertexShaderPath, std::string fragShaderPath) {}

void ShaderProgram::compileCheck(unsigned int shader, bool vertex) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if(vertex) {
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
    }
}

void ShaderProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(this->shaderProgramID, name.c_str()), (int) value);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(this->shaderProgramID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(this->shaderProgramID, name.c_str()), value);
}