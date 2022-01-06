#include <iostream>
#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window

#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <random>
#include <time.h>
// My classes
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include <Circle.h>
#include <Rectangle.h>
#include "Triangle.h"
#include "ShaderManager.h"
#include <RectangleStack.h>
#include <TriangleStack.h>
using namespace shp;
#define DEBUG 1
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
int main() {
    std::cout << "Compiled At: " << __TIME__ << "\n";
    srand(time(NULL));  // initialize random
    // Initialize and configure GLFW -> Set the version &
    // set profile to CORE so we do not get backwards-compatible features.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

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
    ShaderManager shaderManager;
    shaderManager.load_shader("rectangle");
    shaderManager.load_shader("rectstack");    
    shaderManager.load_shader("tristack");
    shaderManager.load_shader("triangle");
    ShaderProgram* triangleShader = shaderManager.getShader("triangle");
    ShaderProgram* rectangleShader =  shaderManager.getShader("rectangle");
    ShaderProgram* rectStackShader =  shaderManager.getShader("rectstack");
    ShaderProgram* triStackShader =  shaderManager.getShader("tristack");
    //RectangleStack rs = RectangleStack(10000, rectStackShader);
    TriangleStack rs = TriangleStack(5, triStackShader);
    rs.initialize(0.1, 0.1);
    rs.randomizeLocations();
    std::cout << "Drawing\n";
    GLenum old_err = GL_NO_ERROR;
    float rot = 0;
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float time = glfwGetTime();
        rs.draw();
        rot += 0.1f;
        if (rot > 5.0f) rot = 0;

        #ifdef DEBUG
        GLenum err = glGetError();
        if (err != old_err && err != GL_NO_ERROR) {
            std::cout << "[DEBUG] GL Error: " << err << "\n";
            old_err = err;
        }
        #endif
        
        glfwSwapBuffers(window);
        // Polls events like keyboard/mouse inputs.
        glfwPollEvents();
    }
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