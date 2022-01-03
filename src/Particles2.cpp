/**
 * @file Particles2.cpp
 * @credit: https://web.engr.oregonstate.edu/~mjb/cs557/Handouts/compute.shader.1pp.pdf
 * @brief Not working, attempt at compute shaders.
 */
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
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


#define NUM_PARTICLES 512 * 512 
#define WORK_GROUP_SIZE 128
// CREDIT: https://web.engr.oregonstate.edu/~mjb/cs557/Handouts/compute.shader.1pp.pdf
struct pos {
    float x, y, z, w;
};
struct vel {
    float vx, vy, vz, vw;
};
struct col {
    float r, g, b, a;
};

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
    VertexBuffer posSSbo;
    VertexBuffer velSSbo;
    VertexBuffer colSSbo;
    posSSbo.bind(GL_SHADER_STORAGE_BUFFER);
    posSSbo.setBufferData(GL_SHADER_STORAGE_BUFFER, 
    NUM_PARTICLES * sizeof(struct pos), NULL, GL_STATIC_DRAW);
    GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
    struct pos *points = (struct pos *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 
                          NUM_PARTICLES * sizeof(struct pos), bufMask );    // creates a pointer to the buffer we can write to.
    for( int i = 0; i < NUM_PARTICLES; i++ ) {
    points[ i ].x = neg_randf();
    points[ i ].y = neg_randf();
    points[ i ].z = neg_randf();
    points[ i ].w = 1.0;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    
    velSSbo.bind(GL_SHADER_STORAGE_BUFFER);
    glBufferData( GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct vel), NULL, GL_STATIC_DRAW );
    struct vel *vels = (struct vel *) glMapBufferRange( GL_SHADER_STORAGE_BUFFER, 0, 
                        NUM_PARTICLES * sizeof(struct vel), bufMask );  // pointer we can write to
    for(int i = 0; i < NUM_PARTICLES; i++ ) {
    vels[ i ].vx = neg_randf();
    vels[ i ].vy = neg_randf();
    vels[ i ].vz = neg_randf();
    vels[ i ].vw = 1.0;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    colSSbo.bind(GL_SHADER_STORAGE_BUFFER);
    colSSbo.setBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct col), NULL, GL_STATIC_DRAW);
    struct col* cols = (struct col *) glMapBufferRange(
                                      GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct col), bufMask);
    
    for(int i = 0; i < NUM_PARTICLES; i++ ) {
    cols[ i ].r = norm_randf();
    cols[ i ].g = norm_randf();
    cols[ i ].b = norm_randf();
    cols[ i ].a = 1.0;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


    // we now have written random values in pos and vel and col buffers.
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, posSSbo.getBuffer());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, velSSbo.getBuffer());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, colSSbo.getBuffer());
    ShaderProgram computeShader = ShaderProgram(ShaderProgram::get_shader_file("compute\\compute.c"));
    computeShader.use();
    std::cout << "Compute time\n";
    glDispatchCompute( NUM_PARTICLES / WORK_GROUP_SIZE, 1, 1 );
    glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
    std::cout << "Render time\n";
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float time = glfwGetTime();

        // glUseProgram( MyRenderingShaderProgram ); what? TODO: make a shader
        glBindBuffer( GL_ARRAY_BUFFER, posSSbo.getBuffer() );
        glVertexPointer( 4, GL_FLOAT, 0, (void *)0 );
        glEnableClientState( GL_VERTEX_ARRAY );
        glDrawArrays( GL_POINTS, 0, NUM_PARTICLES );
        glDisableClientState( GL_VERTEX_ARRAY );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
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
// -1 to 1
float neg_randf() {
    return float(rand()) / float(RAND_MAX) * 2 - 1;
}
float norm_randf() {
    return float(rand()) / float(RAND_MAX);
}