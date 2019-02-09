#include <glad.h>
#include "vectors.h"
#include <stb_image.h>
#include <SDL.h>

typedef struct texture
{
    const char* file_name;
    int width,height,channels;
    GLuint ID;
    GLuint vao;
}texture_t;

typedef struct mesh
{
    GLuint vao;
    GLuint program;
    GLuint shader_position;
    GLuint shader_rotation;
    GLuint shader_scale;
    GLuint buffer[2];
    vector2_t position;
    vector2_t scale;    
    float rotation;
    
    float* vertex;
    float* uv;

    texture_t* texture;
}mesh_t;



void mesh_create(mesh_t* mesh, vector2_t position, GLuint vao);

void get_uniform_locations(mesh_t* mesh);

void set_uniform_locations(mesh_t* mesh);

void set_position(mesh_t *mesh, vector2_t new_position);

void set_rotation(mesh_t *mesh, float new_rotation);

void set_scale(mesh_t *mesh, vector2_t new_scale);

void set_texture(mesh_t *mesh, char* data);

texture_t* create_texture(const char* texture);

void draw(mesh_t* mesh);

void draw_multiple_instance(mesh_t* mesh, GLuint program);

void bind_texture(texture_t*texture,mesh_t* mesh);

void generate_buffers(mesh_t* mesh);

void buffer_create(mesh_t *mesh, vector2_t position);

void mesh_movement(mesh_t*mesh, SDL_Event *event,float velocity, float delta_time);

void mesh_rotation(mesh_t*mesh, SDL_Event *event,float velocity, float delta_time);

void mesh_scaling(mesh_t*mesh, SDL_Event *event,float scaling_factor, float delta_time);



