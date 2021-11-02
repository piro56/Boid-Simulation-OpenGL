#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
uniform vec2 ourPosition;

uniform mat4 transform;

void main()
{
    gl_Position = vec4(aPos.x + ourPosition.x, aPos.y + ourPosition.y, aPos.z, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}