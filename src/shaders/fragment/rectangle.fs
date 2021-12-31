#version 460 core
out vec4 FragColor;

in vec3 ourColor;

uniform vec3 selectedColor;
void main()
{
    // FragColor = vec4(selectedColor, 1.0)
    FragColor = vec4(ourColor, 1.0);
}