#include <window.h>
#include <glad.h>

int create_context(context_t *ctx, int min_version, int max_version, const char *title)
{
    SDL_Init(SDL_INIT_VIDEO);

    if (min_version == 0)
        min_version = 4;

    if (max_version == 0)
        max_version = 4;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, max_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, min_version);


    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ctx->width, ctx->height, SDL_WINDOW_OPENGL );
    
    if (!window)
    {
        printf("Window wasn't initialized : %s", SDL_GetError());
        return -1;
    }

    ctx->window = window;

    
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
    {
        printf("Context wasn' t initialized : %s", SDL_GetError());
        return -1;
    }

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    
    glClearColor(0, 0, 0, 255);

    return 0;
}