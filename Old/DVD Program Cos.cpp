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

#include <windows.h>
#include <filesystem>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

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

    // Two triangles
    float vertices[] = {
    // positions          // colors           // texture coords
     0.25f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.25f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.25f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.25f,  0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };
    VertexArray VAO;
    VAO.bind();
    VertexBuffer VBO;
    VBO.bind();
    ElementBuffer EBO;
    EBO.bind();
    EBO.setData(sizeof(indices), indices, GL_STATIC_DRAW);
    VBO.setBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    VBO.setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    VBO.enableAttribArray(0);
    // color attribute
    VBO.setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VBO.enableAttribArray(1);
    // texture coordinates...
    VBO.setVertexAttributePointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VBO.enableAttribArray(2);

    Texture myTexture = Texture(GL_TEXTURE0);
    myTexture.bindEnable();

    // TEXTURE LOADING 
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //              texture type, axis, wrapping option
    float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    myTexture.setParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    myTexture.setParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    myTexture.setParameterfv(GL_TEXTURE_BORDER_COLOR, borderColor);
    // Texture filtering for magnification and minification
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    myTexture.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    myTexture.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::string pngLocation = ShaderProgram::get_shader_file("imgs\\dvd.png");
    myTexture.loadPNG(pngLocation, true);

    ShaderProgram myShader(ShaderProgram::get_shader_file("vertex\\dvd.vs"),
                           ShaderProgram::get_shader_file("fragment\\dvd.fs"));
/*     ShaderProgram myShader("C:\\Users\\epicp\\Documents\\Programming\\OpenGL-Playground\\src\\shaders\\default.vs",
                           "C:\\Users\\epicp\\Documents\\Programming\\OpenGL-Playground\\src\\shaders\\default.fs"); */
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    myShader.use();
    myShader.setInt("texture1", 0);

    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float offsetValue = sin(timeValue) / 2.0f;
        float offsetValueTwo = cos(timeValue) / 2.0f;
        myTexture.bindEnable();
        VAO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        myShader.use();
        myShader.setVec2Float("dvdOffset", offsetValue, offsetValueTwo);
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

void processMovement(float& x, float& y, float& angle) {
    // angle is the direction of velocity, 0 is straight right, pi is left, 3/2pi is down etc..
    if (x == 1.0 || x == -1.0 || y == 1.0 || y == -1.0) {
        // calculate angle
        // TODO: replace with pi. 
        angle = (3.14 / 2) - angle + 3.14; // 90 - angle + 180
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