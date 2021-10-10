#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;
in vec4 ourPosition;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
    // Set the texture first
    FragColor = texture(texture2, TexCoord);
}