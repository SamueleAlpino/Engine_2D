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
    memset(mesh->uv, 0, sizeof(float) * 12);

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
        0, 1,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0};
    mesh->uv = uv;

    mesh->position = position;
    bind_vbo(mesh);

    get_uniform_locations(mesh);
    set_position(mesh, position);
}

void set_position(mesh_t *mesh, vector2_t new_position)
{
    glUniform2f(mesh->shader_position, new_position.x, new_position.y);
}

void set_rotation(mesh_t *mesh, float new_rotation)
{
    glUniform1f(mesh->shader_rotation, new_rotation);
}

void set_scale(mesh_t *mesh, vector2_t new_scale)
{
    glUniform2f(mesh->shader_scale, new_scale.x, new_scale.y);
}

texture_t *create_texture(const char *texture)
{
    texture_t *tex = malloc(sizeof(texture_t));
    memset(tex, 0, sizeof(texture_t));
    //Load texture
    unsigned char *pixels = stbi_load(texture, &tex->width, &tex->height, &tex->channels, 4);
    tex->file_name = texture;

    if (!pixels)
    {
        printf("texture not initialized");
        return NULL;
    }

    glGenTextures(1, &tex->ID);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex->ID);

    if (tex->channels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(pixels);

    return tex;
}

void bind_texture(texture_t *texture, mesh_t *mesh)
{
    texture->vao = mesh->vao;

    GLint tex_0 = glGetUniformLocation(mesh->program, "tex");

    glUniform1i(tex_0, 0);
}

void buffer_create(mesh_t *mesh, vector2_t position)
{
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);
    mesh->vertex = malloc(sizeof(float) * 18);
    memset(mesh->vertex, 0, sizeof(float) * 18);
    mesh->uv = malloc(sizeof(float) * 12);

    float vertex[] = {
        -1, 1, 0.0, //a
        1, -1, 0.0, //b
        1, 1, 0.0,  //c

        -1, 1, 0.0,  //a
        -1, -1, 0.0, //b
        1, -1, 0.0   //c
    };

    mesh->vertex = vertex;

    float uv[] = {
        0, 1,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0};

    mesh->uv = uv;
    mesh->position = position;

    bind_vbo(mesh);

    get_uniform_locations(mesh);
}

void draw(mesh_t *mesh)
{
    // use program because the pipeline can change
    glUseProgram(mesh->program);
    glBindTexture(GL_TEXTURE_2D, mesh->texture->ID);
    glBindVertexArray(mesh->vao);
    glUniform1i(mesh->texture->ID, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    set_uniform_locations(mesh);
    //   set_position(mesh, mesh->position);
    //   set_scale(mesh, vector2_new(0.5, 0.5));
}

void mesh_movement(mesh_t *mesh, SDL_Event *event, float velocity, float delta_time)
{

    if (event->key.keysym.sym == SDLK_RIGHT)
        mesh->position.x += velocity * delta_time;
    else if (event->key.keysym.sym == SDLK_LEFT)
        mesh->position.x -= velocity * delta_time;
    else if (event->key.keysym.sym == SDLK_UP)
        mesh->position.y += velocity * delta_time;
    else if (event->key.keysym.sym == SDLK_DOWN)
        mesh->position.y -= velocity * delta_time;
}

void mesh_rotation(mesh_t *mesh, SDL_Event *event, float velocity, float delta_time)
{
    if (event->key.keysym.sym == SDLK_RIGHT)
            mesh->rotation -= velocity;
    else if (event->key.keysym.sym == SDLK_LEFT)
            mesh->rotation += velocity;
}

void mesh_scaling(mesh_t *mesh, SDL_Event *event, float scaling_factor, float delta_time)
{
    if (event->key.keysym.sym == SDLK_RIGHT)
        mesh->scale.x -= scaling_factor;
    else if (event->key.keysym.sym == SDLK_LEFT)
        mesh->scale.x += scaling_factor;
    else if (event->key.keysym.sym == SDLK_UP)
        mesh->scale.y += scaling_factor;
    else if (event->key.keysym.sym == SDLK_DOWN)
        mesh->scale.y -= scaling_factor;
}

void generate_buffers(mesh_t *mesh)
{
    GLuint frame_buffers[2];
    glGenFramebuffers(2, frame_buffers);

    GLuint render_textures[2];
    glGenTextures(2, render_textures);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffers[0]);

    glBindTexture(GL_TEXTURE_2D, render_textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, render_textures[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, render_textures[0], 0);
    glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_textures[1], 0);

    mesh->buffer[0] = frame_buffers[0];

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// for post processing change program and shader
// draw
// change program
// draw again with other shader
// swap buffer 0
void draw_multiple_instance(mesh_t *mesh, GLuint program)
{
    //   printf("b : %p\n", &mesh->buffer[0]);
    glBindFramebuffer(GL_FRAMEBUFFER, mesh->buffer[0]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mesh->program);

    glBindVertexArray(mesh->vao);

    glBindTexture(GL_TEXTURE_2D, mesh->texture->ID);

    glUniform1i(mesh->texture->ID, 0);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(program);

    GLint tex_0 = glGetUniformLocation(mesh->program, "tex");

    glBindTexture(GL_TEXTURE_2D, mesh->texture->ID);

    glBindVertexArray(mesh->vao);

    glUniform1i(tex_0, 0);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2);
}