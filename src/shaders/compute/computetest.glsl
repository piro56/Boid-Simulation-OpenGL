#version 460 code
#extension GL_ARB_compute_shader : enable

// particles
// X, Y, Z
// Vx, Vy, Vz
// 
layout (std430, binding=3) buffer Pos {
    vec4 Positions[];
}
layout (std430, binding=4) buffer Vel {
    vec4 Velocities[];
}

layout (std430, binding=5) buffer Col {
    vec4 Colors[];  // RGB (then maybe shadow)
}

void main() {
    
}


