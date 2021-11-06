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

#include <thread>
#include <atomic>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
void process_Movement_Thread(std::vector<Fish*>& triangles, int begin, int end);                     
float randomColor();
std::atomic<bool> runThreads (true);
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main() {
    // Initialize and configure GLFW -> Set the version &
    // set profile to CORE so we do not get backwards-compatible features.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create window object.
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
    for (int i = 0; i < 3200; i++) {
        triangles.push_back(new Fish (0.005, 0.01, &triangles));
        triangles[i]->setColor(200 / 255.0f, 20.0f/255.0f, 20.0f/255.0f);

        //triangles[i]->setColor(randomColor(), randomColor(), randomColor());
    }
    for (Fish* t : triangles) {
            t->processMovement();
        }
    // Render loop
    #define NUM_THREADS 8
    std::thread threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i ++) {
        threads[i] = std::thread(process_Movement_Thread, 
        std::ref(triangles), i * triangles.size() / NUM_THREADS, (i+1) * triangles.size() / NUM_THREADS);
    }
    float lastTimeValue = 0;
    while (!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        process_input(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float offOne = (sin(timeValue)) / 2.0f;
        float offTwo = (cos(timeValue)) / 2.0f;
        int counter = 0;
        for (Fish* t : triangles) {
            //t->processMovement();
            //counter++;
            //t->setPosition(t->getX() + (rand() % 3 - 1) * rand() % 200 / 20000.0f, t->getY() + (rand() % 3 - 1) * rand() % 200 / 20000.0f);
            t->draw();
        }
        // Swapping buffers reduces artifacts.
        glfwSwapBuffers(window);
        // Polls events like keyboard/mouse inputs.
        glfwPollEvents();
    }
    runThreads = false;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    for (auto tri : triangles) {
        delete tri;
    }
    glfwTerminate();
    return 0;
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

void process_Movement_Thread(std::vector<Fish*>& triangles, int begin, int end) {
    while(runThreads) {
        for (volatile int i = begin; i < end; i++) {
            triangles[i]->processMovement();
        }
    }
}