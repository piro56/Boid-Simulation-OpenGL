#include <iostream>
#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window

#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h" // image loading

// GUI
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <stdio.h>

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
const char* glsl_version = "#version 150";
FishSettings fs_default = {
    .0005, 0.01, 0.000005, 0.00002, 0.04, 0.005, 0.001, 0.000375, 1.0
};
FishSettings fs = {
    .0005, 0.01, 0.000005, 0.00002, 0.04, 0.005, 0.001, 0.000375, 1.0
};
FishSettings& Fish::FISH_SETTINGS = fs;
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
    for (int i = 0; i < 1600; i++) {
        triangles.push_back(new Fish (0.005, 0.01, &triangles));
        triangles[i]->setColor(200 / 255.0f, 20.0f/255.0f, 20.0f/255.0f);

        //triangles[i]->setColor(randomColor(), randomColor(), randomColor());
    }
    // for (Fish* t : triangles) {
    //         t->processMovement();
    // }
    // Render loop
    #define NUM_THREADS 8
    std::thread threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i ++) {
        threads[i] = std::thread(process_Movement_Thread, 
        std::ref(triangles), i * triangles.size() / NUM_THREADS, (i+1) * triangles.size() / NUM_THREADS);
    }

    // GUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    bool show_demo_window = false;
    bool show_another_window = false;
    float avoidance_dist_mult = 1.0f;
    float speed_mult = 1.0f;
    float avoidance_turn_mult = 1.0f;
    while (!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        glfwPollEvents();
        process_input(window);
        fs.AVOID_DIST_THRESHOLD = fs_default.AVOID_DIST_THRESHOLD * avoidance_dist_mult;
        fs.AVOID_STRENGTH = fs_default.AVOID_STRENGTH * avoidance_turn_mult;
        fs.MAX_SPEED = fs_default.MAX_SPEED * speed_mult;
        fs.MIN_SPEED = fs_default.MIN_SPEED * speed_mult;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&show_demo_window);
        {
            // simple slider window
            ImGui::Begin("BOID Settings");
            ImGui::SliderFloat("Avoidance Distance", &avoidance_dist_mult, 0.001f, 5.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
            ImGui::SliderFloat("Size", &fs.SIZE, 0.01f, 10.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
            ImGui::SliderFloat("Avoidance Strength", &avoidance_turn_mult, 0.01f, 5.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
            ImGui::SliderFloat("Speed", &speed_mult, 0.1f, 10.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
            ImGui::End();
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float offOne = (sin(timeValue)) / 2.0f;
        float offTwo = (cos(timeValue)) / 2.0f;
        int counter = 0;
        for (Fish* t : triangles) {
            //t->processMovement();
            //t->setPosition(t->getX() + (rand() % 3 - 1) * rand() % 200 / 20000.0f, t->getY() + (rand() % 3 - 1) * rand() % 200 / 20000.0f);
            t->draw();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swapping buffers reduces artifacts.
        glfwSwapBuffers(window);
        // Polls events like keyboard/mouse inputs.
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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