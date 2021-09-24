#include <iostream>     
#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window
#include "VertexBuffer.h"
#include "VertexArray.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void compileCheck(unsigned int vertexShader);
void linkCheck(unsigned int shaderProgram);
void process_input(GLFWwindow *window);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\nvoid main(){FragColor = vec4(0.2f, 0.5f, 0.2f, 1.0f);}\0";
    const char *fragmentShaderTwoSource = "#version 330 core\n"
    "out vec4 FragColor;\nvoid main(){FragColor = vec4(0.9f, 0.9f, 0.1f, 1.0f);}\0";
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

    // Two triangles, to create a square.
    float verticesOriginal[] = {
        -0.3f, -0.5f, 0.0f, // bottom left
        0.3f, -0.5f, 0.0f,  // bottom right
        0.0f,  0.75f, 0.0f,  // middle
    };
    float vertices[] = {
        -0.6f, 0.0f, 0.0f,  // BLL
        0.0f, 0.0f, 0.0f,   // BR
        -0.3f, 0.6f, 0.0f,  // TM
        0.6f, 0.0f, 0.0f,   // BRR
        0.3f, 0.6f, 0.f     // TRM
    };
    unsigned int indices[] = {
        0,1,2,
        1,3,4 
    };
    VertexArray VAO;
    VAO.bind();
    VertexBuffer VBO;
    VBO.bind();
    VBO.setBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    VBO.setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    VBO.enableAttribArray(0);
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    /*
    // Use VAO, easier and I believe needed to draw objects.
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);     // bind & configure corresponding VBO's ->  unbind

    // Create memory on the GPU to store vertex data
    // Vertex buffer object stores vertices on GPU memory
    unsigned int VBO, VBOTwo;
    glGenBuffers(1, &VBO);  // Generate 1 buffer, save it to VBO
    glGenBuffers(1, &VBOTwo);
    // Specify buffer type, this is the type of a vertex array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     
    // From here on out, all calls on "GL_ARRAY_BUFFER" will now be on VBO.
    // glBufferData copies defined vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // VERTEX ATTRIB POINTER tells GPU how to interpret shader data.
    // In Vertex Shader: location = 0, this sets vertex attrib array location 0.
    // This function applies to the currently bound VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    // Bind second buffer, and read in it's data and how to interpret.
    glBindBuffer(GL_ARRAY_BUFFER, VBOTwo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOriginal), verticesOriginal, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    // Enable vertex attribute with it's location
    glEnableVertexAttribArray(0);

    // Element buffer object, to create a square...
    // instead of needing 6 points, we can use 4 and create 2 triangles.
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0) <- Draw for the indices.
    */

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);    // Create a shader

    // Attach shader source code to our created shader & compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    compileCheck(vertexShader);
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    compileCheck(fragmentShader);

    // Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);   // cleanup
    glDeleteShader(fragmentShader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Render loop
    while(!glfwWindowShouldClose(window))
    {   
        process_input(window);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        VAO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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