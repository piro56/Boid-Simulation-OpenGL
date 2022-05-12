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

using namespace shp;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
float neg_randf();
float norm_randf();
void fillRand(float* arr, int size, bool neg = true, float modifier = 1.0f);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {
    std::cout << "Compile Time: " << __TIME__ << "\n";
    srand(time(NULL));  // initialize random
    // Initialize and configure GLFW -> Set the version &
    // set profile to CORE so we do not get backwards-compatible features.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    
    int num_particles = 128;
    
    VertexBuffer pSSBO, vSSBO, cSSBO;
    
    float *pos = new float[num_particles * 4];
    float *vel = new float[num_particles * 4];
    float *col = new float[num_particles * 4];
    
    fillRand(pos, num_particles * 4, true, 1.0f);
    fillRand(vel, num_particles * 4, true, 0.2f);
    fillRand(col, num_particles * 4, false, 1.0f);

    pSSBO.bind(GL_SHADER_STORAGE_BUFFER);
    pSSBO.setBufferData(GL_SHADER_STORAGE_BUFFER, 
    num_particles * 4 * sizeof(float), pos, GL_DYNAMIC_DRAW);

    vSSBO.bind();
    vSSBO.setBufferData(GL_SHADER_STORAGE_BUFFER, 
    num_particles * 4 * sizeof(float), vel, GL_DYNAMIC_DRAW);

    cSSBO.bind();
    cSSBO.setBufferData(GL_SHADER_STORAGE_BUFFER, 
    num_particles * 4 * sizeof(float), col, GL_DYNAMIC_DRAW);
    
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, pSSBO.getBuffer());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, vSSBO.getBuffer());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, cSSBO.getBuffer());

    ShaderProgram computeShader = 
    ShaderProgram(ShaderProgram::get_shader_file("compute\\computetest.glsl"));

    computeShader.use();
    glDispatchCompute(num_particles / 128, 1, 1);
    glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    
    // TODO: Read back positions to see if compute shader succeeeded
    pSSBO.bind();
    float* posdata = (float*) glMapNamedBuffer(pSSBO.getBuffer(), GL_READ_ONLY);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "Error: " << err << "\n";
    }

    // unmap buffer
    std::cout << "pos 0: " << posdata[0] << posdata[1] << posdata[2] << posdata[3] << "\n";
    bool result = glUnmapNamedBuffer(pSSBO.getBuffer());
    if (result == GL_FALSE) {
        std::cout << "bad buffer!\n";
    }
    shaderManager.load_shader("particle");
    ShaderProgram* draw_shader = shaderManager.getShader("particle");
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    while(!glfwWindowShouldClose(window))
    {
        //compute
        // computeShader.use();
        // glDispatchCompute(num_particles / 128, 1, 1);
        // glMemoryBarrier(GL_ALL_BARRIER_BITS);
        if (err != GL_NO_ERROR) {
        std::cout << "Error: " << err << "\n";
        }
        
        //draw
        draw_shader->use();
        glBindBuffer( GL_ARRAY_BUFFER, pSSBO.getBuffer() );
        glVertexAttribPointer(0, 3 * num_particles, GL_FLOAT, GL_FALSE, 
                              4 * sizeof(float), (void*) 0);
        glEnableClientState( GL_ARRAY_BUFFER );

        glDrawArrays(GL_POINTS, 0, num_particles);
        if (err != GL_NO_ERROR) {
            std::cout << "Error: " << err << "\n";
        }
        process_input(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float time = glfwGetTime();

        //t.draw();
        glfwSwapBuffers(window);
        // Polls events like keyboard/mouse inputs.
        glfwPollEvents();
    }
    delete[] pos;
    delete[] vel;
    delete[] col;
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

// -1 to 1
float neg_randf() {
    return float(rand()) / float(RAND_MAX) * 2 - 1;
}
// 0 to 1
float norm_randf() {
    return float(rand()) / float(RAND_MAX);
}

void fillRand(float* arr, int size, bool neg, float modifier) {
    for (int i = 0; i < size; i++) {
        if (neg) {
            arr[i] = neg_randf();
        } else {
            arr[i] = norm_randf();
        }
    }
}