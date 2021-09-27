#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec4 ourPosition;
void main()
{
    FragColor = ourPosition;
}