#include <iostream>
#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window

#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h" // image loading

// My classes
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Triangle.h"
#include "Fish.h"

#include <windows.h>
#include <filesystem>
#include <math.h>
#include <cstdlib>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
void processMovement(float& x, float& y, float& dx, float& dy, 
                     float& angle, float xBorder, float yBorder, 
                     float& r, float &g, float& b);
float randomColor();
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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
    // TEXTURE LOADING 
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    srand(time(NULL));
    float pixels[800][600];
    for (int i = 0; i < 800; i++) {
        for (int j = 0; j < 600; j++) {
            pixels[i][j] = 0.0f;
        }
    }
    float dx = 0.0165;
    float dy = -0.015;
    float angle = 0.95;
    float xValue = 0.14 + dx;
    float yValue = 0.02 + dy;
    std::vector<Fish*> triangles;
    for (int i = 0; i < 400; i++) {
        triangles.push_back(new Fish (0.01, 0.03, &triangles));
        triangles[i]->setColor(randomColor(), randomColor(), randomColor());
    }
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float offOne = (sin(timeValue)) / 2.0f;
        float offTwo = (cos(timeValue)) / 2.0f;
        int counter = 0;
        for (Fish* t : triangles) {
            t->processMovement();
            //counter++;
            //t->setPosition(t->getX() + (rand() % 3 - 1) * rand() % 200 / 20000.0f, t->getY() + (rand() % 3 - 1) * rand() % 200 / 20000.0f);
            t->draw();
        }
        // Swapping buffers reduces artifacts.
        glfwSwapBuffers(window);
        // Polls events like keyboard/mouse inputs.
        glfwPollEvents();
    }
    for (auto tri : triangles) {
        delete tri;
    }
    glfwTerminate();
    return 0;
}

void processMovement(float& x, float& y, float& dx, float& dy, float& angle, float xBorder, float yBorder, float& r, float &g, float& b) {
    // angle is the direction of velocity, 0 is straight right, pi is left, 3/2pi is down etc..
    if (x + xBorder >= 1.0 || x - xBorder <= -1.0) {
        // random between 0 and 255
        r = randomColor();
        g = randomColor();
        b = randomColor();
        dx = -dx;
    } else if (y  + yBorder >= 1.0 || y - yBorder <= -1.0) {
        r = randomColor();
        g = randomColor();
        b = randomColor();
        dy = -dy;
    }
}
float randomColor() {
    return (rand() % 255 + 10) / 255.0f;
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