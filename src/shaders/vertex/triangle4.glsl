#version 460 core
layout (location = 0) in vec4 aPos;



out vec4 ourColor;
out vec4 gl_Position;
//out float gl_PointSize;
void main()
{
    gl_Position = aPos;
    gl_PointSize = 1;
    ourColor = vec4(0.7, 0.1, 0.1, 1.0);
}