#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
out vec4 trianglePos;
uniform vec2 ourPosition;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    trianglePos = gl_Position;
    ourColor = aColor;
    TexCoord = aTexCoord;
}