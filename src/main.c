#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <obj_parser.h>

// #define triangle_def(x0, y0, z0, x1, y1, z1, x2, y2, z2) \
//     triangle_new(                                    \
//         vertex_new(vector3_p_new(x0, y0, z0)),         \
//         vertex_new(vector3_p_new(x1, y1, z1)),         \
//         vertex_new(vector3_p_new(x2, y2, z2)))

int main(int argc, char **argv)
{
    ctx_t* ctx = create_ctx(600,600);
    obj_file_t* file_obg = malloc(sizeof(obj_file_t));
    memset(file_obg,0, sizeof(obj_file_t));
//     triangle_t*  triangle   = triangle_new(vertex_new(0, 0.5, 0),
//                                           vertex_new(0, -0.5, 0),
//                                           vertex_new( 0.5, 0, 0)); 
//    append_triangle(triangle,ctx);

  //  printf("x :%f y  :%f\n" , triangle->a.position.x,triangle->a.position.y);
  //  printf("x :%f y  :%f\n" , triangle->b.position.x,triangle->b.position.y);
  //  printf("x :%f y  :%f\n" , triangle->c.position.x,triangle->c.position.y);

    // triangle_t*  triangle = triangle_new(vertex_new(0.5, 0.5, 0),
    //                                        vertex_new( 0.5, -0.5, 0),
    //                                        vertex_new( 0, 0, 0));
    // append_triangle(triangle,ctx);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Render", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, ctx->width,ctx->height,0);
    
    if (!window)
        return -1;
    
    SDL_Renderer *renderer= SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    
    if (!renderer)
        return -1;

    SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,600,600);
    
    
    char* data = read_file("D:/Sam/Convert_point/Stormtrooper.obj",&file_obg->file_size);
    parse_obj(ctx,data,file_obg);
    parse_obj_faces(ctx,data,file_obg);


    for(;;)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;

            if(event.type == SDL_KEYDOWN)
            {
                ctx->camera->x -= 10;
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_LEFT:
                        ctx->camera->x -= 0.1;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        ctx->camera->x +=0.1;
                        break;             
                    case SDL_SCANCODE_DOWN:
                        ctx->camera->y +=0.1;
                        break;
                    case SDL_SCANCODE_UP:
                        ctx->camera->y -=0.1;
                        break; 
                    case SDL_SCANCODE_W:
                        ctx->camera->z +=0.1;
                        break; 
                    case SDL_SCANCODE_S:
                        ctx->camera->z -=0.1;
                        break; 
                    default:
                        break;
                }      
                    
            }
        }
        int pitch;

        SDL_LockTexture(texture, NULL ,(void**)&ctx->frame_buffer, &pitch);
        
        clear_screen(ctx);

        for(int i = 0; i < ctx->number_of_triangle; i++)
            rendering(ctx, i,255,255,0);

       // printf("Current index: %d  Number of triangle :%zu\n", i ,ctx->number_of_triangle);
       // put_pixel_from_point(ctx,300,300,255,0,0);

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
       
    }


    return 0;
}
