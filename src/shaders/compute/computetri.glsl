#version 460 core
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

// particles
// X, Y, Z
// Vx, Vy, Vz
// 

// specify work group size
layout( local_size_x = 128, local_size_y = 1, local_size_z = 1 ) in;

layout( std430, binding=3 ) buffer Pos {
    vec4 Positions[];
};
layout(std430, binding=4) buffer Vel {
    vec4 Velocities[];
};

layout(std430, binding=5) buffer Col {
    vec4 Colors[];  // RGB (then maybe shadow)
};

void main() {
    // shift positions by velocity.
    Positions[gl_GlobalInvocationID.x].xy += Velocities[gl_GlobalInvocationID.x].xy;
    if (abs(Positions[gl_GlobalInvocationID.x].x) >= 1.0) {
        Velocities[gl_GlobalInvocationID.x].x = -Velocities[gl_GlobalInvocationID.x].x;
    }
    if (abs(Positions[gl_GlobalInvocationID.x].y) >= 1.0) {
        Velocities[gl_GlobalInvocationID.x].y = -Velocities[gl_GlobalInvocationID.x].y;
    }

}


