#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in vec2 uv_out[];
in vec3 vertex_color[];

out vec2 uv_frag;
out vec3 v_color;

void main()
{
    vec4 v1 = gl_in[1].gl_Position - gl_in[0].gl_Position;
    vec4 v2 = gl_in[2].gl_Position - gl_in[0].gl_Position;

    vec3 v_f = normalize(cross(normalize(v1.xyz),normalize(v2.xzy)));
    

    gl_Position = gl_in[0].gl_Position + vec4(v_f,0)  * -0.5;
    v_color = vertex_color[0];
    uv_frag = uv_out[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(v_f,0) * -0.5;
    v_color = vertex_color[1];
    uv_frag = uv_out[1];
    EmitVertex();
  //3 fra 0 e 2     
    gl_Position = ((gl_in[2].gl_Position +gl_in[0].gl_Position)/2)  + vec4(v_f,0)  * -0.5;
    vec2 new_uv = (uv_out[2] + uv_out[0])/2;
    v_color = vertex_color[2];
    uv_frag = new_uv;
    EmitVertex();
    
    EndPrimitive();
    
    gl_Position = gl_in[1].gl_Position + vec4(v_f,0) * 1;
     v_color = vertex_color[1];
    uv_frag = uv_out[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + vec4(v_f,0)  *1;
    v_color = vertex_color[2];
    uv_frag = uv_out[2];
    EmitVertex();

    gl_Position = ((gl_in[2].gl_Position +gl_in[0].gl_Position)/2)  + vec4(v_f,0)  * 1;
    v_color = vertex_color[2];
    uv_frag = new_uv;
    EmitVertex();

    EndPrimitive();

}