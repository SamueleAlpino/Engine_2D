#version 410 core

//il colore in uscita
out vec4 color;

in vec3 vertex_color;
in vec3 vertex_pos;
in vec2 uv_out;

uniform sampler2D tex;

void main()
{

   vec3 base_color = texture(tex,vec2(uv_out.x,1-uv_out.y)).xyz;
    
   color =  vec4(base_color ,1);

   // color = vec4(vertex_color,1);

}