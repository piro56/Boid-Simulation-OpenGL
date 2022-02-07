#version 460 core
layout (location = 0) in vec4 aPos;
// Particle Vertex Shader, does nothing.
layout(std430, binding=5) buffer Col {
    vec4 Colors[];  // RGB (then maybe shadow)
};


out vec4 ourColor;
out vec4 gl_Position;
out float gl_PointSize;
void main()
{
    ourColor = Colors[0];
    gl_Position = aPos;
    gl_PointSize = 100.0;
}