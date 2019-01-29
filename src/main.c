//clang -Wno-pragma-pack -o Engine2D.exe -I SDL2-2.0.9\include -I header -I stb_image.h -I glad\include -I glad\include\glad  glad\src\glad.c src\main.c src\window.c src\vectors.c src\shader_utils.c src\renderer.c -lSDL2 -L.
#define STB_IMAGE_IMPLEMENTATION
#define SDL_MAIN_HANDLED
#include <stb_image.h>
#include <shader_utils.h>

int main(int argc, char **argv)
{

    context_t *context = malloc(sizeof(context_t));
    memset(context, 0, sizeof(context_t));
    context->width = 800;
    context->height = 600;

    create_context(context, 4, 4, "engine");

    GLuint program = create_program("vertex.glsl", "frag.glsl", front);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    mesh_t *mesh = malloc(sizeof(mesh_t));
    memset(mesh, 0, sizeof(mesh_t));
    mesh->program = program;
    mesh_create(mesh, vector2_zero(),mesh->vao);

    int w, h, comp;
    unsigned char *pixels = stbi_load("idle.png", &w, &h, &comp, 4);

    if (!pixels)
    {
        printf("texture not initialized");
        return -1;
    }

    mesh_t *ole = malloc(sizeof(mesh_t));
    memset(ole, 0, sizeof(mesh_t));
    ole->program = program;
    mesh_create(ole, vector2_new(10,1),mesh->vao);

    glBindVertexArray(mesh->vao);
    
    GLuint tex;

    glGenTextures(1,&tex);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    free(pixels);

    GLint tex_0 = glGetUniformLocation(mesh->program,"tex");
    
    glUniform1i(tex_0, 0);
    
    int state = 0;

    for (;;)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return 0;

                if (state == 0)
                {
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        mesh->rotation.y += 1;
                    else if (event.key.keysym.sym == SDLK_LEFT)
                        mesh->rotation.y -= 1;
                    else if (event.key.keysym.sym == SDLK_UP)
                        mesh->rotation.x += 1;
                    else if (event.key.keysym.sym == SDLK_DOWN)
                        mesh->rotation.x -= 1;
                    else if (event.key.keysym.sym == SDLK_2)
                        state = 1;
                    else if (event.key.keysym.sym == SDLK_3)
                        state = 2;
                }
                else if (state == 1)
                {
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        mesh->position.x += 0.2;
                    else if (event.key.keysym.sym == SDLK_LEFT)
                        mesh->position.x -= 0.2;
                    else if (event.key.keysym.sym == SDLK_UP)
                        mesh->position.y += 0.2;
                    else if (event.key.keysym.sym == SDLK_DOWN)
                        mesh->position.y -= 0.2;
                    else if (event.key.keysym.sym == SDLK_1)
                        state = 0;
                    else if (event.key.keysym.sym == SDLK_3)
                        state = 2;
                }
                else if (state == 2)
                {
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        mesh->scale.x += 0.1;
                    else if (event.key.keysym.sym == SDLK_LEFT)
                        mesh->scale.x -= 0.1;
                    else if (event.key.keysym.sym == SDLK_UP)
                        mesh->scale.y += 0.1;
                    else if (event.key.keysym.sym == SDLK_DOWN)
                        mesh->scale.y -= 0.1;
                    else if (event.key.keysym.sym == SDLK_1)
                        state = 0;
                    else if (event.key.keysym.sym == SDLK_2)
                        state = 1;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        set_uniform_locations(mesh);
      

        //renderizza i valori che vanno tra 0 e 1 con la pipeline che gli ho definito prima

        glDrawArrays(GL_TRIANGLES,0, 6);

        set_uniform_locations(ole);

        glDrawArrays(GL_TRIANGLES,0, 6);
        
        //bindo mesh
        //bindo texture
        


        SDL_GL_SwapWindow(context->window);
    }

    return 0;
}