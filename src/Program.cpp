#include <iostream>
#include <math.h>
#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void compileCheck(unsigned int vertexShader);
void linkCheck(unsigned int shaderProgram);
void process_input(GLFWwindow *window);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";
int main() {
    // Initialize and configure GLFW -> Set the version &
    // set profile to CORE so we do not get backwards-compatible features.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window object.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make 'window' the current context on the current thread.
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Window dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // When window is resized -> call frambuffer_size_callback.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Two triangles
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    VertexArray VAO;
    VAO.bind();
    VertexBuffer VBO;
    VBO.bind();
    VBO.setBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    VBO.setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    // color attribute
    VBO.setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    VBO.enableAttribArray(0);
    VBO.enableAttribArray(1);

    ShaderProgram myShader("C:\\Users\\epicp\\Documents\\Programming\\OpenGL-Playground\\src\\shaders\\default.vs", 
                           "C:\\Users\\epicp\\Documents\\Programming\\OpenGL-Playground\\src\\shaders\\default.fs");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        VAO.bind();
        myShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        // Swapping buffers reduces artifacts.
        glfwSwapBuffers(window);
        // Polls events like keyboard/mouse inputs.
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
// When user resizes window, resize the window in OpenGL to the new width and height
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void compileCheck(unsigned int vertexShader) {
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void linkCheck(unsigned int shaderProgram) {
        int  success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
}
