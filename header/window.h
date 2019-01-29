#include <SDL.h>
#include <stdio.h>

typedef struct context{
   // int screen_size[2];
    int width;
    int height;
    SDL_Window *window;
    float delta_time;
}context_t;

int create_context(context_t * ctx, int min_version, int max_version,const char* title);
