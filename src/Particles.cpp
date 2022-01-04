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
using namespace shp;
#define DEBUG 1
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
int main() {
    std::cout << "Compile Time: " << __TIME__ << "\n";
    srand(time(NULL));  // initialize random
    // Initialize and configure GLFW -> Set the version &
    // set profile to CORE so we do not get backwards-compatible features.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    ShaderManager shaderManager;
    shaderManager.load_shader("rectangle");
    shaderManager.load_shader("rectstack");
    shaderManager.load_shader("triangle");
    ShaderProgram* triangleShader = shaderManager.getShader("triangle");
    ShaderProgram* rectangleShader =  shaderManager.getShader("rectangle");
    ShaderProgram* rectStackShader =  shaderManager.getShader("rectstack");
    Triangle t = Triangle(0.5, 0.5, triangleShader);
    shp::Rectangle r = shp::Rectangle(0.001f, 0.001f, rectangleShader);
    t.setColor(0.5, 0.2, 0.2);
    RectangleStack rs = RectangleStack(2, rectStackShader);
    rs.initialize(0.02, 0.02);
    //rs.randomizeLocations();

    std::cout << "Drawing\n";
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float time = glfwGetTime();
        r.setRotation(cos(time) * 10);
        r.setPosition(r.getX(), sin(time)/2);
        rs.setPosition(0, cos(time)/2, sin(time)/2, 0.0f);
        rs.setPosition(1, sin(time)/2, cos(time)/2, 0.0f);
        rs.draw();
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