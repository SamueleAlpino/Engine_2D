#version 410 core

//il colore in uscita
out vec4 color;

in vec2 uv_out;
in vec3 vertex_color;

uniform sampler2D tex;

void main()
{
   vec4 texture      =  texture(tex,vec2(uv_out.x,1-uv_out.y));
   vec3 base_color   = texture.xyz;
   float trasparence = 1 - (1 -texture.w);
   
   color =  vec4(base_color + vertex_color ,trasparence);

   // color = vec4(vertex_color,1);

}