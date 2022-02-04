#version 460 core
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

// credit https://web.engr.oregonstate.edu/~mjb/cs557/Handouts/compute.shader.1pp.pdf

// in uvec3 gl_NumWorkGroups;          // Same numbers as in the glDispatchCompute call
// const uvec3 gl_WorkGroupSize;       // Same numbers as in the layout local_size_* 
// in uvec3 gl_WorkGroupID;            // which workgroup this thread is in
// in uvec3 gl_LocalInvocationID;      // where this thread is in the workgroup
// in uvec3 gl_GlobalInvocationID;     // where this thread is in ALL work items
// in uint gl_LocalInvocationIndex     // 1d representation of gl_LocalInvocationID
/*
gl_LocalInvocationIndex =     gl_LocalInvocationID.z * gl_WorkGroupSize.y * gl_WorkGroupSize.x +
gl_LocalInvocationID.y * gl_WorkGroupSize.x + gl_LocalInvocationID.x
*/ 

layout( std430, binding=4 ) buffer Pos
{
vec4 Positions[ ]; // array of structures
};

layout( std430, binding=5 ) buffer Vel
{
vec4 Velocities[ ]; // array of structures
};

layout( std430, binding=6 ) buffer Col
{
vec4 Colors[ ]; // array of structures
};

// WHAT does this do?
// defines our local size                                                                                                                                                       
layout( local_size_x = 128, local_size_y = 1, local_size_z = 1 ) in;

vec3 Bounce( vec3 vin, vec3 n ) {
    vec3 vout = reflect( vin, n );
    return vout;
}
vec3 BounceSphere( vec3 p, vec3 v, vec4 s ) {
    vec3 n = normalize( p - s.xyz );
    return Bounce( v, n );
}
bool IsInsideSphere( vec3 p, vec4 s ) {
    float r = length( p - s.xyz );
    return ( r < s.w );
}

void main() 
{
    const vec4 Sphere = vec4( -100., -800., 0., 600. ); // x, y, z, r 
    const vec3 G = vec3( 0., -9.8, 0. );
    const float DT = 0.1;
    uint gid = gl_GlobalInvocationID.x; // the .y and .z are both 1 in this case

    vec3 p = Positions[ gid ].xyz;
    vec3 v = Velocities[ gid ].xyz;

    // calculate next frame
    vec3 pp = p + v * DT + .5 * DT * DT * G;
    vec3 vp = v + G*DT;
    if( IsInsideSphere( pp, Sphere ) ) {
        vp = BounceSphere( p, v, Sphere );
        pp = p + vp*DT + .5*DT*DT*G;
    }
    Positions[ gid ].xyz = pp;
    Velocities[ gid ].xyz = vp;
}


