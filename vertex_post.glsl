#version 410 core

layout (location = 0) vec3 vertex;
layout (location = 1) vec2 uv;

out vec3 v_color;
out vec2 uv_out;

void main()
{
    gl_Position = vec4(vertex,1);
    v_color = vec3(1,0,0);
    uv_out = uv;
}