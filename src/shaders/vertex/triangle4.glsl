#version 460 core
layout (location = 0) in vec4 aPos;

out vec4 ourColor;
out vec4 gl_Position;
//out float gl_PointSize;
void main()
{
    ourColor = vec4(0.5, 0.1, 0.3, 1.0);
    gl_Position =  aPos;
}