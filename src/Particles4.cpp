#include <iostream>
#include <glad/glad.h>  // Manages function pointers
#include <glfw3.h>      // Manages window

<<<<<<< HEAD
#include <glm/glm.hpp>  // matrix math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <cstdlib>
=======
// #include <glm/glm.hpp>  // matrix math
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <math.h>
// #include <cstdlib>
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
#include <vector>
#include <random>
#include <time.h>
// My classes
#include "VertexBuffer.h"
<<<<<<< HEAD
=======
#include "GLBuffer.h"
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "ElementBuffer.h"
#include "Texture.h"
<<<<<<< HEAD
#include <Circle.h>
#include <Rectangle.h>
#include "Triangle.h"
#include "ShaderManager.h"

using namespace shp;
=======
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "ShaderManager.h"

using namespace shp; // namespace for certain shapes
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
float neg_randf();
float norm_randf();
<<<<<<< HEAD
void fillRand(float* arr, int size, bool neg = true, float modifier = 1.0f);
=======
void fillRand(float* arr, int size, bool neg = true, float multiplier = 1.0f);
void gl_check_error();
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {
    std::cout << "Compile Time: " << __TIME__ << "\n";
    srand(time(NULL));  // initialize random
<<<<<<< HEAD
=======

>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
    // Initialize and configure GLFW -> Set the version &
    // set profile to CORE so we do not get backwards-compatible features.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

<<<<<<< HEAD
    if (window == NULL)
    {
=======
    if (window == NULL) {
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make 'window' the current context on the current thread.
    glfwMakeContextCurrent(window);

<<<<<<< HEAD
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
    
=======

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // Window dimensions
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // When window is resized -> call frambuffer_size_callback.
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ShaderManager shaderManager;
    GLBuffer pSSBO = GLBuffer(GL_SHADER_STORAGE_BUFFER);
    GLBuffer vSSBO = GLBuffer(GL_SHADER_STORAGE_BUFFER);
    GLBuffer cSSBO = GLBuffer(GL_SHADER_STORAGE_BUFFER);
    GLBuffer regVBO = GLBuffer(GL_ARRAY_BUFFER);
    VertexArray vao;
    int num_points = 1048576;
    int num_floats = num_points * 4;

    float *pos = new float[num_floats];
    float *vel = new float[num_floats]; // x y pad pad
    float *col = new float[num_floats]; // r g b pad

    fillRand(pos, num_floats, true);
    fillRand(vel, num_floats, true, 0.001);
    fillRand(col, num_floats, false);

    vao.bind();
    pSSBO.bind();
    pSSBO.setBufferData(num_floats * sizeof(float), pos, GL_DYNAMIC_DRAW);
    vSSBO.bind();
    vSSBO.setBufferData(num_floats * sizeof(float), vel, GL_DYNAMIC_DRAW);
    cSSBO.bind();
    cSSBO.setBufferData(num_floats * sizeof(float), col, GL_DYNAMIC_DRAW);
    gl_check_error();
    std::cout << "Buffer Base\n";
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, pSSBO.getBuffer());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, vSSBO.getBuffer());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, cSSBO.getBuffer());

    ShaderProgram computeShader = 
<<<<<<< HEAD
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
=======
    ShaderProgram(ShaderProgram::get_shader_file("compute\\computetri.glsl"));
    gl_check_error();
    // std::cout << "Pre Compute:\n";
    // computeShader.use();
    // glDispatchCompute(num_points / 128, 1, 1);
    // glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    // gl_check_error();
    // std::cout << "Computed\n";
    pSSBO.bind();

    // read back data
    float* posdata = (float*) glMapNamedBuffer(pSSBO.getBuffer(), GL_READ_ONLY);
    gl_check_error();

    // unmap buffer
    std::cout << "pos: " << posdata[0] << ", " << posdata[1] << ", " << posdata[2] << ", " << posdata[3] << "\n";
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
    bool result = glUnmapNamedBuffer(pSSBO.getBuffer());
    if (result == GL_FALSE) {
        std::cout << "bad buffer!\n";
    }
<<<<<<< HEAD
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
=======
    shaderManager.load_shader("triangle4");
    ShaderProgram* draw_shader = shaderManager.getShader("triangle4");
    gl_check_error();
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    draw_shader->use();
    glBindBuffer(GL_ARRAY_BUFFER, pSSBO.getBuffer());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 
                          4 * sizeof(float), (void*) 0);  
    glEnable(GL_PROGRAM_POINT_SIZE);
    while(!glfwWindowShouldClose(window)) {
        computeShader.use();
        glDispatchCompute(num_points / 128, 1, 1);
        glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
        process_input(window);
        glClearColor(0.0f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_shader->use();
        gl_check_error();
        vao.bind();

        //draw
        glDrawArrays(GL_POINTS, 0, num_points);   
        

        glfwSwapBuffers(window);
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
        glfwPollEvents();
    }
    delete[] pos;
    delete[] vel;
    delete[] col;
}

<<<<<<< HEAD
void process_input(GLFWwindow *window)
{
=======

// Processes user input
void process_input(GLFWwindow *window)
{
    // ESC -> Close Window

>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

<<<<<<< HEAD

=======
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
// When user resizes window, resize the window in OpenGL to the new width and height
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// -1 to 1
float neg_randf() {
<<<<<<< HEAD
    return float(rand()) / float(RAND_MAX) * 2 - 1;
=======
    float val = ((float(rand()) / float(RAND_MAX)) * 2.0) - 1.0;
    return val;
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
}
// 0 to 1
float norm_randf() {
    return float(rand()) / float(RAND_MAX);
}

<<<<<<< HEAD
void fillRand(float* arr, int size, bool neg, float modifier) {
    for (int i = 0; i < size; i++) {
        if (neg) {
            arr[i] = neg_randf();
        } else {
            arr[i] = norm_randf();
        }
    }
=======
/*
 * Fills array with random numbers -1 to 1 or 0 to 1
 * neg - whether or not values can be negative
 */
void fillRand(float* arr, int size, bool neg, float multiplier) {
    for (int i = 0; i < size; i++) {
        if (neg) {
            arr[i] = neg_randf() * multiplier;
        } else {
            arr[i] = norm_randf() * multiplier;
        }
    }
}

void gl_check_error() {
    GLenum err = GL_NO_ERROR;
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "Error: " << err << "\n";
    }
>>>>>>> 820dede23fd2af0269c07f60762d1a9e966bd109
}