#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 selectedColor;
void main()
{
    FragColor = vec4(selectedColor, 1.0);
}