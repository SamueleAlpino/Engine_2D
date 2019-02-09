#version 410 core
out vec4 color;

in vec3 v_color;
in vec2 uv_out;

uniform sampler2D tex;

void main()
{   
   vec3 base_color = texture(tex,vec2(uv_out.x, 1 - uv_out.y)).xyz;

   color =  vec4(base_color - v_color,1);
}