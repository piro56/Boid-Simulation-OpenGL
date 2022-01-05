#version 460 core
#extension GL_NV_shader_buffer_load : enable
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTranslation;

struct Transformation {
    vec4 offset;    // 4
    vec3 scale;     // 3 floats
    float rotation; // 1 float
                    // 8 total
};

layout (std430, binding = 3) buffer transform {
    Transformation transformations[];
};
mat4 idenMat = mat4(1.0, 0.0, 0.0, 0.0,  
                    0.0, 1.0, 0.0, 0.0, 
                    0.0, 0.0, 1.0, 0.0,  
                    0.0, 0.0, 0.0, 1.0);
                    
// CREDIT: http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
mat4 rotationMat(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}
mat4 transMat(vec3 trans) {
    return mat4(1.0, 0.0, 0.0, 0.0,  
                0.0, 1.0, 0.0, 0.0, 
                0.0, 0.0, 1.0, 0.0,  
                trans.x, trans.y, trans.z, 1.0);
}

out vec3 ourColor;
int index = gl_VertexID / 6;

void main()
{

    gl_Position = transMat(transformations[index].offset.xyz)
     * rotationMat(vec3(0.0, 0.0, 1.0), transformations[index].rotation) 
     * vec4(aPos, 1.0);

    //gl_Position = vec4(aPos + transformations[index].offset, 1.0); 
    ourColor = vec3(index / 10.0, 0.0, 0.2);
}