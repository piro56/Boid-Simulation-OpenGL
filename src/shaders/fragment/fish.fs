#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec4 trianglePos;
uniform vec3 selectedColor;
void main()
{
    float rC = sqrt(abs(trianglePos.x));
    float gC = sqrt(abs(trianglePos.y));
    float bC = exp2(rC * gC);
    FragColor = vec4(rC, gC, bC, 1.0);
}