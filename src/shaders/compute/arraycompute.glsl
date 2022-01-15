#version 460 core
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout (std430, binding = 3) readonly buffer Data {
    vec2 datapts[];
}
// we segment the output ourselves
layout (std430, binding = 4) writeonly buffer Output_Data {
    vec2 outputpts[];
}

uint gid = gl_GlobalInvocationID.x
uniform float xbound;
uniform float ybound;
uniform int num_segments;

void main() {
    // for our current index on datapts 
    // we will check where it is and put it in its corrective place in outputpts.    
    
    datapts[gid].x / 
}