#version 330 core
layout (location = 0) in vec4 aPos; // the position variable has attribute position 0

uniform mat4 u_projection;
uniform mat4 u_model;

void main()
{
    gl_Position = u_projection * u_model * aPos; // see how we directly give a vec3 to vec4's constructor
}
