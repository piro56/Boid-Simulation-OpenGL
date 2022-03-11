#version 460 core
out vec4 FragColor;

in vec4 ourColor;

void main()
{
    // Set the texture first
    FragColor = ourColor;
}