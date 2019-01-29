#version 410 core

const float PI = 3.1415926535;

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;

uniform vec2 position;
uniform vec2 rotation;
uniform vec2 scale;

vec2 const_scale; 

out vec2 uv_out;
out vec3 vertex_color;

float linear_converter(float value, float old_min, float old_max, float new_min, float new_max)
{
    float gradient = (value - old_min) /(old_max - old_min);
    return new_min + gradient * (new_max - new_min);
}

float rotate_x(vec2 vertex, float angle)
{
    angle = radians(angle);
    vec2 vertex0 = vertex;
    vertex.y = vertex0.y * cos(angle);
    return vertex.y;
}

float rotate_y(vec2 v, float angle)
{
    angle = radians(angle);
    vec2 v0 = v;
    v.x = v0.x * cos(angle);
    return v.x;
}

void main()
{
    const_scale = scale + vec2(1,1);
  
    vec2 new_pos ;
    new_pos.x = vertex.x + position.x ;
    new_pos.y = vertex.y + position.y; 
    gl_Position = vec4( new_pos.x* const_scale.x, new_pos.y * const_scale.y ,0,1) ;
    uv_out = uv;
    vertex_color     = vec3(1,0,0);
}

