#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in vec4 ourPosition;
uniform sampler2D texture1;
void main()
{
    FragColor = texture(texture1, TexCoord);
    if(FragColor.a == 0.0) {
        //discard;
        FragColor = vec4(0.5,0.1,0.0,1.0);
    } 
}