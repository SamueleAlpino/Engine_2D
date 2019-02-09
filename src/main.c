//clang -Wno-pragma-pack -o Engine2D.exe -I SDL2-2.0.9\include -I header -I stb_image.h -I glad\include -I glad\include\glad  glad\src\glad.c src\main.c src\window.c src\vectors.c src\shader_utils.c src\renderer.c -lSDL2 -L.
#define STB_IMAGE_IMPLEMENTATION
#define SDL_MAIN_HANDLED
#include <window.h>
#include <shader_utils.h>
#include <glad.h>

int main(int argc, char **argv)
{
    // size_t current_time = SDL_GetPerformanceCounter();
    // size_t last_time = 0;

    // double deltaTime = 0;

    context_t *context = malloc(sizeof(context_t));
    memset(context, 0, sizeof(context_t));
    context->width = 800;
    context->height = 600;

    create_context(context, 4, 4, "engine");

    GLuint program = create_program_vf("vertex.glsl", "frag.glsl");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    texture_t *texture = create_texture("idle.png");

    mesh_t *robot = malloc(sizeof(mesh_t));
    memset(robot, 0, sizeof(mesh_t));
    robot->program = program;

    mesh_create(robot, vector2_new(200, 400), robot->vao);
    robot->texture = texture;

    bind_texture(texture, robot);

    // mesh_t *robot_2 = malloc(sizeof(mesh_t));
    // memset(robot_2, 0, sizeof(mesh_t));
    // robot_2->program = program;

    // mesh_create(robot_2, vector2_new(0,0),robot_2->vao);
    // robot_2->texture = texture;

    // bind_texture(texture,robot_2);

    // set_position(robot_2, vector2_new(0,0));
    // GLuint color = glGetUniformLocation(mesh->program, "color_in");
    // glUniform1fv( color,6,color_array);

    // mesh_t *other = malloc(sizeof(mesh_t));
    // memset(other, 0, sizeof(mesh_t));

    //  buffer_create(other,vector2_zero());
    // other->program = program;
    // mesh_create(other,vector2_new(0.5,0.5), other->vao);
    // other->texture = texture;
    // bind_texture(texture,other);
    // GLint tex_0 = glGetUniformLocation(mesh->program,"tex");

    // generate_buffers(other);
    // glUniform1i(tex_0, 0);

    int state = 0;

    for (;;)
    {
        // last_time = current_time;
        // current_time = SDL_GetPerformanceCounter();

        // deltaTime = (double)((current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());
        // deltaTime = (double)((current_time - last_time) / (double)SDL_GetPerformanceFrequency());
        
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;

            if (event.key.keysym.sym == SDLK_ESCAPE)
                return 0;

            //printf("delta time : %f\n", deltaTime);

            
            if (state == 0)
            {
                mesh_movement(robot, &event, 100, 0.03);

                if (event.key.keysym.sym == SDLK_2)
                    state = 1;
                else if (event.key.keysym.sym == SDLK_3)
                    state = 2;
            }
            else if (state == 1)
            {
                mesh_rotation(robot, &event, 2, 0.03);

                if (event.key.keysym.sym == SDLK_1)
                    state = 0;
                else if (event.key.keysym.sym == SDLK_3)
                    state = 2;
            }
            else if (state == 2)
            {
                mesh_scaling(robot, &event, 0.1,  0.03);

                if (event.key.keysym.sym == SDLK_1)
                    state = 0;
                else if (event.key.keysym.sym == SDLK_2)
                    state = 1;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        draw(robot);
        //   draw(robot_2);
        SDL_GL_SwapWindow(context->window);

        //  glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    return 0;
}
