#include <glad.h>
#include "vectors.h"

typedef struct mesh
{
    GLuint vao;
    GLuint program;
    GLuint shader_position;
    GLuint shader_rotation;
    GLuint shader_scale;
    vector2_t position;
    vector2_t rotation;
    vector2_t scale;    
    
    float* vertex;
    float* uv;
}mesh_t;

void mesh_create(mesh_t* mesh, vector2_t position, GLuint vao);

void get_uniform_locations(mesh_t* mesh);

void set_uniform_locations(mesh_t* mesh);

void set_position(mesh_t *mesh, vector2_t new_position);

void set_rotation(mesh_t *mesh, vector2_t new_rotation);

void set_scale(mesh_t *mesh, vector2_t new_scale);

void set_texture(mesh_t *mesh, char* data);


