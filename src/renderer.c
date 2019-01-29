#include <renderer.h>
#include <stdlib.h>
#include <stdio.h>

static void bind_vbo(mesh_t *mesh)
{
    GLuint vbo[2];
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    //carico i dati nel vbo 0
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), (void *)mesh->vertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    //l attributo 0 lavora su oggetti con dimensione 3
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), (void *)mesh->uv, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void get_uniform_locations(mesh_t *mesh)
{
    mesh->shader_position = glGetUniformLocation(mesh->program, "position");
    mesh->shader_rotation = glGetUniformLocation(mesh->program, "rotation");
    mesh->shader_scale = glGetUniformLocation(mesh->program, "scale");
}

void set_uniform_locations(mesh_t *mesh)
{
    set_position(mesh, mesh->position);
    set_rotation(mesh, mesh->rotation);
    set_scale(mesh, mesh->scale);
}

void mesh_create(mesh_t *mesh, vector2_t position, GLuint vao)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    mesh->vao = vao;
    mesh->vertex = malloc(sizeof(float) * 18);
    memset(mesh->vertex, 0, sizeof(float) * 18);
    mesh->uv = malloc(sizeof(float) * 12);
    float vertex[] = {
        -0.5, 0.5, 0.0, //a
        0.5, -0.5, 0.0, //b
        0.5, 0.5, 0.0,  //c

        -0.5, 0.5, 0.0,  //a
        -0.5, -0.5, 0.0, //b
        0.5, -0.5, 0.0   //c
    };

    mesh->vertex = vertex;

    float uv[] = {
        0,1,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0
        };

    mesh->uv = uv;

    bind_vbo(mesh);

    get_uniform_locations(mesh);

    set_scale(mesh, vector2_new(1, 1));

    set_position(mesh, position);
}

void set_position(mesh_t *mesh, vector2_t new_position)
{
    glUniform2f(mesh->shader_position, new_position.x, new_position.y);
}

void set_rotation(mesh_t *mesh, vector2_t new_rotation)
{
    glUniform2f(mesh->shader_rotation, new_rotation.x, new_rotation.y);
}

void set_scale(mesh_t *mesh, vector2_t new_scale)
{
    glUniform2f(mesh->shader_scale, new_scale.x, new_scale.y);
}
