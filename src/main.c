#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <utils.h>
#include <SDL.h>

#define triangle(x0, y0, z0, x1, y1, z1, x2, y2, z2) \
    triangle_new(                                    \
        vertex_new(vector3_new(x0, y0, z0)),         \
        vertex_new(vector3_new(x1, y1, z1)),         \
        vertex_new(vector3_new(x2, y2, z2)))


int main(int argc, char **argv)
{
    ctx_t ctx;
    ctx.width = 600;
    ctx.height = 600;
    ctx.frame_buffer = NULL;

    triangle_t triangle = triangle(0, 0.5, 0, -0.5, 0, 0, 0.5, 0, 0);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Render", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, ctx.width,ctx.height,0);
    if (!window)
        return -1;
    SDL_Renderer *renderer= SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    if (!renderer)
        return -1;

    SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,600,600);
    
    for(;;)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            return 0;
        }
        int pitch;
        SDL_LockTexture(texture, NULL ,(void **)&ctx.frame_buffer, & pitch);

        rasterize(&ctx, &triangle);

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);

        clear_screen(&ctx);

    }


    return 0;
}
