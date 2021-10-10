#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec4 ourPosition;
uniform sampler2D texture1;
void main()
{
    // Set the texture first
    FragColor = texture(texture1, vec2(TexCoord.x, TexCoord.y));
}