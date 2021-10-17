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
#include "Camera.h"

#include <windows.h>
#include <filesystem>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void process_input(GLFWwindow *window);
void mouse_scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
bool cursor = false;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f; 


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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    /*
    // Two triangles
    float vertices[] = {
    // positions          // colors           // texture coords
     0.25f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.25f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.25f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.25f,  0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    */
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
    EBO.setData(sizeof(indices), indices, GL_DYNAMIC_DRAW);
    VBO.setBufferData(sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    // position attribute, stride of 5 floats
    VBO.setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    VBO.enableAttribArray(0);
    // color attribute
    //VBO.setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //VBO.enableAttribArray(1);
    // texture coordinates...
    VBO.setVertexAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VBO.enableAttribArray(1);

    Texture myTexture = Texture(GL_TEXTURE0);
    myTexture.bindEnable();

    // TEXTURE LOADING 
    
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //              texture type, axis, wrapping option
    float borderColor[] = { 0.0f, 0.2f, 0.0f, 0.0f };
    myTexture.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    myTexture.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    //myTexture.setParameterfv(GL_TEXTURE_BORDER_COLOR, borderColor);
    // Texture filtering for magnification and minification
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    myTexture.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    myTexture.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::string pngLocation = ShaderProgram::get_shader_file("imgs\\dvd.png");
    myTexture.loadPNG(pngLocation, true);
    Texture crateTexture = Texture(GL_TEXTURE1);
    crateTexture.bindEnable();
    crateTexture.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    crateTexture.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    //crateTexture.setParameterfv(GL_TEXTURE_BORDER_COLOR, borderColor);
    crateTexture.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    crateTexture.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    crateTexture.loadJPG(ShaderProgram::get_shader_file("imgs\\container.jpg"), false);
    ShaderProgram myShader(ShaderProgram::get_shader_file("vertex\\matting.vs"),
                           ShaderProgram::get_shader_file("fragment\\matting.fs"));    myShader.use();
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);

    // GLM     
    /*
    // ROTATE AND SCALE.
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    myShader.setMatrix4f("transform", false, glm::value_ptr(trans));
    */
    /* TRANSLATION
    //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);          // identity matrix with diagonols set to 1.0f
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));    // create the translation matrix. Translating X and Y 
    vec = trans * vec;  // Apply transformation to vec
    std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
    */
    
    // CAMERA
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);   // negate the vector, normalize
    // up vector, then get cross products for x, y
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    //glm::vec3 cameraRight = glm::cross(up, cameraDirection);
    //glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    const float radius = 1.0f;
    



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        // per frame logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        process_input(window);

        // offsets
        float offsetValue = cos(currentFrame);
        float offsetValueTwo = sin(currentFrame);
        float normalizedOffsetValue = (offsetValue + 2) / 2;
        float normalizedOffsetValueTwo = (offsetValueTwo + 2) / 2;
        
        // render
        glClearColor(0.4f, 0.1f, 0.8f, 1.0f);
        //glClearColor(normalizedOffsetValueTwo, normalizedOffsetValueTwo, normalizedOffsetValue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind textures and shaders
        myTexture.bindEnable();
        crateTexture.bindEnable();
        myShader.use();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::mat4(1.0);

        VAO.bind();
        // set the perspective to camera fov, aspect ratio, and the rendering of near/far.
        projection = glm::perspective(glm::radians(camera.Zoom), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);
        // move the scene back. (everything we're drawing.)
        myShader.setMatrix4f("projection", false, glm::value_ptr(projection));
        myShader.setMatrix4f("view",  false, glm::value_ptr(view));
        
        for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians((20.0f * (i+1))), glm::vec3((offsetValue + 2.0f) / 2.0f, 0.3f, 0.5f));
        myShader.setMatrix4f("model", false, glm::value_ptr(model));
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        }


        /*
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(offsetValueTwo, offsetValue, 0.0f));
        trans = glm::rotate(trans, (float) timeValue, glm::vec3(1.0, 0.0, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5f, (offsetValue + 2)/2, 0.5f));
        myShader.setMatrix4f("transform", false, glm::value_ptr(trans));
        */
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //myShader.use();
        //myShader.setVec2Float("dvdOffset", offsetValue, offsetValueTwo);
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
        cursor = !cursor;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED - (2 * cursor));

        //glfwSetWindowShouldClose(window, true);
    } 
}
// When user resizes window, resize the window in OpenGL to the new width and height
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false; 
    }
    float xOff = xPos - lastX;
    float yOff = lastY - yPos;  // reversed since Ycoordinates go top to bottom

    camera.ProcessMouseMovement(xOff, yOff, true);
}

void mouse_scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(yOffset);
}