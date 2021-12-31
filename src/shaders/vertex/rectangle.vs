#version 460 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform vec2 ourPosition;

uniform mat4 transform;

void main()
{
    // gl_Position = transform * vec4(aPos, 1,0);
    gl_Position = vec4(aPos, 1.0);
    // ourColor = aColor;
    ourColor = vec3(0.2, 0.7, 0.3);
}