#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 ourColor;
uniform mat4 rectTrans;

void main()
{

    gl_Position = rectTrans * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = vec3(0.2, 0.7, 0.3);
}