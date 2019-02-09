#version 410 core

const float PI = 3.1415926535;

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;

uniform vec2 position;
uniform float rotation;
uniform vec2 scale;

vec2 const_scale; 

out vec2 uv_out;
out vec3 vertex_color;

//uniform float color_in[6];

float linear_converter(float value, float old_min, float old_max, float new_min, float new_max)
{
    float gradient = (value - old_min) /(old_max - old_min);
    return new_min + gradient * (new_max - new_min);
}

vec3 rotate(vec3 v, float angle)
{
    angle = radians(angle);
    vec3 v0 = v;
    v.x = v0.x * cos(angle) + v0.y * -sin(angle);
    v.y = v0.x * sin(angle) + v0.y * cos(angle);
    return v;
}

void main()
{
    const_scale = scale + vec2(1,1);
    
    float screen_pos_x = linear_converter(position.x,0,800,-1,1);
    float screen_pos_y = linear_converter(position.y,0,600,-1,1);

    vec2 new_pos ;

    new_pos.x = (rotate(vertex, rotation).x + screen_pos_x ) * const_scale.x ;
    new_pos.y = (rotate(vertex, rotation).y   + screen_pos_y ) * const_scale.y ; 

    gl_Position  = vec4( new_pos.x * 600/800, new_pos.y ,0,1) ;
   
    vertex_color = vec3(0,0,0);
    uv_out = uv;
}



// void main()
// {
//     const_scale = scale + vec2(1,1);
    
//     float screen_pos_x = linear_converter(position.x,0,800,-1,1);
//     float screen_pos_y = linear_converter(position.y,0,600,-1,1);

//     vec2 new_pos ;

//     if(gl_InstanceID == 0)
//     {
//         new_pos.x = (vertex.x  + screen_pos_x)* const_scale.x ;
//         new_pos.y = (vertex.y  + screen_pos_y)* const_scale.y ; 

//     }
//     else
//     {
//         new_pos.x = (vertex.x * const_scale.x) ;
//         new_pos.y = (vertex.y * const_scale.y) ; 
//     }
    
//     gl_Position = vec4( new_pos.x, new_pos.y  ,0,1) ;
   
//     vertex_color     = vec3(color_in[gl_InstanceID * 3 ],color_in[(gl_InstanceID * 3) + 1 ],color_in[(gl_InstanceID*3) +2]);
//     uv_out = uv;
// }

