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
#include "ShaderManager.h"
#include "GLBuffer.h"


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