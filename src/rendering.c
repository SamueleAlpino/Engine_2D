#include <rendering.h>

#define M_PI 3.1415926

void put_pixel(vector2_int_t *vertex_pos, ctx_t *context, unsigned char R, unsigned char G, unsigned char B)
{
    if (vertex_pos->x < 0 || vertex_pos->x > context->width - 1)
        return;
    if (vertex_pos->y < 0 || vertex_pos->y > context->height - 1)
        return;
    //(y*width+x)*4;
    int index = ((vertex_pos->y * context->width) + vertex_pos->x) * 4;
    //BLUE
    context->frame_buffer[index] = B;
    //GREEN
    context->frame_buffer[index + 1] = G;
    //RED
    context->frame_buffer[index + 2] = R;

    context->frame_buffer[index + 3] = 0;

}

int append_triangle(triangle_t* value, ctx_t* ctx)
{
    ctx->number_of_triangle++;
    triangle_t *resized_area = realloc(ctx->array_of_triangle,sizeof(triangle_t) * ctx->number_of_triangle);
    if(!resized_area)
        return -1;        
  
    ctx->array_of_triangle = resized_area;
    ctx->array_of_triangle[ ctx->number_of_triangle - 1] = *value;

    return 0;
}

ctx_t* create_ctx(int width, int height)
{
    ctx_t* to_return = malloc(sizeof(ctx_t));
    memset(to_return,0,sizeof(ctx_t));
    to_return->array_of_triangle = NULL;
    to_return->frame_buffer = NULL;
    to_return->width = width;
    to_return->height = height;
    to_return->camera = vector3_p_new(0,0,-5);
    to_return->number_of_triangle = 0;
    return to_return;
}

vertex_t* vertex_new(float x, float y, float z)
{
    vertex_t* vertex = malloc(sizeof(vertex_t));
    memset(vertex,0,sizeof(vertex_t));
  //  printf("vertex\n");
    vertex->position.x = x;
    vertex->position.y = y;
    vertex->position.z = z;
    //vertex->position = *position;
    // vertex->color = vector3_zero();
    // vertex->normal = vector3_zero();
    // vertex->raster_x = 0;
    // vertex->raster_y = 0;
    // vertex->view_position = vector3_zero();
    
    return vertex;
}

triangle_t* triangle_new(vertex_t* a, vertex_t* b, vertex_t* c)
{
    // printf("x :%f y  :%f\n" ,a->position.x,a->position.y);
    // printf("x :%f y  :%f\n" ,b->position.x,b->position.y);
    // printf("x :%f y  :%f\n" ,c->position.x,c->position.y);

   // triangle_t triangle = {.a = a, .b = b, .c = c};
    triangle_t* triangle = malloc(sizeof(triangle_t));
    triangle->a = *a;
    triangle->b = *b;
    triangle->c = *c;
    printf("triangle x pos a :%f\n b :%f\n c :%f\n --------\n", triangle->a.position.x, triangle->b.position.x , triangle->c.position.x);
    return triangle;
}

void view_to_raster(ctx_t *ctx, vertex_t* vertex)
{
    float fov = (60.0 / 2) * (M_PI / 180.0);
    float camera_distance = tan(fov);
    float projected_x = vertex->view_position.x / (camera_distance * vertex->view_position.z);
    float projected_y = vertex->view_position.y / (camera_distance * vertex->view_position.z);
    vertex->raster_x = point_to_screen(projected_x, ctx->width,0);
    vertex->raster_y = point_to_screen(projected_y, ctx->height,1);

  //Debug
    // printf("fov: %f\n", fov);
    // printf("camera distance: %f\n", camera_distance);
    // printf("projected_x : %f\n", projected_x);
    // printf("projected_y : %f\n", projected_y);
    // printf("raster_x : %d\n", vertex->raster_x );
    // printf("raster_y : %d\n", vertex->raster_y );

}

void set_view_pos(ctx_t *ctx, triangle_t* triangle)
{
   // printf("x :%f\n" ,  triangle->a.view_position.x);
    //printf("camera: %f\n",ctx->camera.x);
   // printf("view :%f\n",triangle->a.view_position.x);
    
    triangle->a.view_position.x = triangle->a.position.x - ctx->camera->x;
    triangle->a.view_position.y = triangle->a.position.y - ctx->camera->y;
    triangle->a.view_position.z = triangle->a.position.z - ctx->camera->z;

    triangle->b.view_position.x = triangle->b.position.x - ctx->camera->x;
    triangle->b.view_position.y = triangle->b.position.y - ctx->camera->y;
    triangle->b.view_position.z = triangle->b.position.z - ctx->camera->z;

    triangle->c.view_position.x = triangle->c.position.x - ctx->camera->x;
    triangle->c.view_position.y = triangle->c.position.y - ctx->camera->y;
    triangle->c.view_position.z = triangle->c.position.z - ctx->camera->z;

    view_to_raster(ctx, &triangle->a);
    view_to_raster(ctx, &triangle->b);
    view_to_raster(ctx, &triangle->c);
}

void draw_line(float start_y, float start_x, float end_x, float end_y, ctx_t *ctx) //float p_0_y, float p_0_x, float p_1_y, float p_1_x,float p_2_y,float p_2_x,ctx_t* context)
{
    for (float i = start_y; i < end_y; i++)
    {
        float gradient_pixel_p0_p1 = gradient(i, end_y, start_y);

        float lerp_value = lerp(end_x, start_x, gradient_pixel_p0_p1);
        vector2_int_t pixel;
        pixel.y = i;
        pixel.x = lerp_value;

        put_pixel(&pixel, ctx,255,0,0);

    }
}

void put_pixel_from_point( ctx_t *context,float x, float y, unsigned char R, unsigned char G, unsigned char B)
{
    if (x < 0 || x >= context->width)
        return;
    if (y < 0 || y >= context->height)
        return;
    //(y*width+x)*4;
    int index = ((y * context->width) + x) * 4;
    //BLUE
    context->frame_buffer[index] = B;
    //GREEN
    context->frame_buffer[index + 1] = G;
    //RED
    context->frame_buffer[index + 2] = R;

    context->frame_buffer[index + 3] = 255;
}

void rendering(ctx_t * context, int index, unsigned char R, unsigned char G, unsigned char B)
{
    //Calculate field of view
    set_view_pos(context, &context->array_of_triangle[index]);
    
    //Sort vertex based on Y, from low to high
    vertex_t ordered[3]= {context->array_of_triangle[index].a,context->array_of_triangle[index].b,context->array_of_triangle[index].c};
    
    // vertex_t* ordered = malloc(sizeof(vertex_t)*3);
    // ordered[0] = context->array_of_triangle[index].a;
    // ordered[1] = context->array_of_triangle[index].b;
    // ordered[2] = context->array_of_triangle[index].c;

    vertex_t temp;

    if (ordered[1].raster_y < ordered[0].raster_y)
    {
        temp = ordered[0];
        ordered[0] = ordered[1];
        ordered[1] = temp;
    }

    if (ordered[2].raster_y < ordered[1].raster_y)
    {
        temp = ordered[2];
        ordered[2] = ordered[1];
        ordered[1] = temp;
    }

    if (ordered[1].raster_y < ordered[0].raster_y)
    {
        temp = ordered[0];
        ordered[0] = ordered[1];
        ordered[1] = temp;
    }
    
    //Debug
    // printf("0 :%f\n" ,   ordered[0].position.y);
    // printf("1 :%f\n" ,   ordered[1].position.y);
    // printf("2 :%f\n" ,   ordered[2].position.y);
    // printf("0 raster :%d\n" ,   ordered[0].raster_y);
    // printf("1 raster :%d\n" ,   ordered[1].raster_y);
    // printf("2 raster :%d\n" ,   ordered[2].raster_y);

    //calculate slope
  //  printf("x0 :%d x1:%d y0 : %d y1: %d\n",ordered[0].raster_x, ordered[1].raster_x, ordered[0].raster_y, ordered[1].raster_y);
   
    int slope;
    
    float value_0; 
    float value_1;

    if(ordered[0].raster_y == ordered[1].raster_y)
        value_0 = 1;
    else
        value_0 = inversed_slope(ordered[0].raster_x, ordered[1].raster_x, ordered[0].raster_y, ordered[1].raster_y);
    
    if(ordered[0].raster_y == ordered[2].raster_y)
        value_1 = 1;
    else
        value_1 = inversed_slope(ordered[0].raster_x, ordered[2].raster_x, ordered[0].raster_y, ordered[2].raster_y);
 
    //if value 0 is bigger than 1 , p0 position is right else il left
    if (value_0 > value_1)
        slope = 0;
    else
        slope = 1;

    //Debug
    // printf("value 0 :%f\n",value_0);
    // printf("value 1 :%f\n",value_1);
    // printf("slope :%d\n",slope);
    
    float gradient_var;
    float x_start;
    float x_end;
    int i;

    for (i = ordered[0].raster_y; i < ordered[1].raster_y; i++)
    {
        //calculate gradient and find X
        //if there are point with same y , don' t calculate gradient
        gradient_var = gradient(i, ordered[0].raster_y, ordered[1].raster_y);
        x_start = lerp(ordered[0].raster_x, ordered[1].raster_x, gradient_var);
        printf("x start:%f\n",x_start);
       
        gradient_var = gradient(i, ordered[0].raster_y, ordered[2].raster_y);

            //Thankful to lerp, we calculate the two point for drawing pixels            
        x_end = lerp(ordered[0].raster_x,ordered[2].raster_x, gradient_var);
        printf("x end:%f\n",x_end);
        
        if (slope == 0)
        {
            for (int j = x_start; j < x_end; j++)
                put_pixel_from_point(context, j,i,R,G,B);
        }
        else
        {
            for (int j = x_end; j < x_start; j++)
                put_pixel_from_point(context, j,i,R,G,B);
        }

        //wireframe
        put_pixel_from_point(context, x_start, i,255,0,0);
        put_pixel_from_point(context, x_end, i,255,0,0);

    }

    for (i = ordered[1].raster_y; i < ordered[2].raster_y; i++)
    {
        gradient_var = gradient(i, ordered[1].raster_y, ordered[2].raster_y);
        x_start = lerp(ordered[1].raster_x, ordered[2].raster_x, gradient_var);
        
        gradient_var = gradient(i, ordered[0].raster_y, ordered[2].raster_y);
        x_end = lerp(ordered[0].raster_x,ordered[2].raster_x, gradient_var);

        if (slope == 0)
        {
            for (int j = x_start; j < x_end; j++)
                put_pixel_from_point(context, j,i,R,G,B);
        }
        else
        {
            for (int j = x_end; j < x_start; j++)
                put_pixel_from_point(context, j,i,R,G,B);
        }

        //wireframe
        put_pixel_from_point(context, x_start, i,255,0,0);
        put_pixel_from_point(context, x_end, i,255,0,0);

    }

}

void clear_screen(ctx_t *context)
{
    memset(context->frame_buffer, 0, context->width * context->height * 4);
}