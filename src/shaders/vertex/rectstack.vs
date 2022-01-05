#version 460 core
#extension GL_NV_shader_buffer_load : enable
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTranslation;
layout (std430, binding = 2) buffer translation {
    mat4 transmat;
};

struct Transformation {
    vec3 offset;
    vec3 scale;
    float rotation;
};

layout (std430, binding = 3) buffer transform {
    Transformation transformations[];
};
out vec3 ourColor;

int index = gl_VertexID / 6;

void main()
{
    mat4 idenMat = mat4(1.0, 0.0, 0.0, 0.0,  
                        0.0, 1.0, 0.0, 0.0, 
                        0.0, 0.0, 1.0, 0.0,  
                        0.0, 0.0, 0.0, 1.0);
    mat4 translatedMat = idenMat;
    // TRANSLATION: (note we use key major indexing)
    translatedMat[3][0] = transformations[index].offset.x;
    translatedMat[3][1] = transformations[index].offset.y;
    translatedMat[3][2] = transformations[index].offset.z;


    
    gl_Position = translatedMat * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos + transformations[index].offset, 1.0); 
    ourColor = vec3(index / 2.0, 0.0, 0.0);
}