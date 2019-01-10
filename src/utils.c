#include <utils.h>

//screen_point : 600 = point : 2

//SCREEN_POINT
//screen_point = x
//x : 600 = point : 2
//x = (600 * point)/2

//POINT
//point = x
//screen_point : width = x : 2
//x = (screen_point * 2 ) / width

vector3_t vector3_new(float x,float y , float z)
{
    vector3_t to_return = { .x = x , .y = y, .z = z};
    return to_return;
}

vector3_t vector3_zero()
{
    vector3_t zero = { .x = 0, .y = 0, .z = 0};
    
    return zero;
   // zero.x = _mm_setzero_ps(); 
}

vector2_t point_to_screen(float point_x, float point_y, int screen_width, int screen_height)
{
    vector2_t screen_point;
    screen_point.x = ((point_x + 1) * screen_width)/2;
    screen_point.y = ((point_y + 1) * screen_height)/2;
    return screen_point;
}

vector2_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height)
{
    vector2_t point;

    point.x = ((screen_point_x * 2)/screen_width)-1;
    point.y = ((screen_point_y * 2)/screen_height)-1;

    return point;
}

void point_to_screen_ref(vector2_t* point, int screen_width, int screen_height )
{
    point->x = (( point->x + 1) * screen_width) /2;
    point->y = (( point->y + 1) * screen_height)/2;
}

void screen_to_point_ref(vector2_t* screen_point, int screen_width, int screen_height)
{
    screen_point->x = ((screen_point->x * 2)/screen_width)-1;
    screen_point->y = ((screen_point->y * 2)/screen_height)-1;
}

vertex_t vertex_new(vector3_t position)
{
    vertex_t vertex;
    memset(&vertex, 0, sizeof(vertex_t));
    vertex.position = position; 
    return vertex;
}

triangle_t triangle_new(vertex_t a, vertex_t b, vertex_t c)
{
    triangle_t triangle = {.a = a, .b = b, .c = c};
    return triangle;
}

void rasterize(ctx_t *context,triangle_t *triangle)
{
    vector2_t vertex_a = point_to_screen(triangle->a.position.x,triangle->a.position.y,context->width, context->height);
    vector2_t vertex_b = point_to_screen(triangle->b.position.x,triangle->b.position.y,context->width, context->height);
    vector2_t vertex_c = point_to_screen(triangle->c.position.x,triangle->c.position.y,context->width, context->height);

    put_pixel(&vertex_a,context);
    put_pixel(&vertex_b,context);
    put_pixel(&vertex_c,context);
}

void put_pixel(vector2_t *vertex_pos,ctx_t *context)
{
    //vector2_t vertex_pos = point_to_screen(vertex_pos->x,vertex_pos->y,context.width, context.height);

    if (vertex_pos->x < 0 || vertex_pos->x > context->width - 1)
        return;
    if (vertex_pos->y < 0 || vertex_pos->y > context->height - 1)
        return;

    int index = (vertex_pos->y * context->width * 3) + (vertex_pos->x * 3);
    int backR = context->frame_buffer[index];
    int backG = context->frame_buffer[index + 1];
    int backB = context->frame_buffer[index + 2];
    context->frame_buffer[index]     = 1 + backR;
    context->frame_buffer[index + 1] = 1 + backG;
    context->frame_buffer[index + 2] = 1 + backB;
}


void clear_screen(ctx_t *context)
{
    memset((void*)context->frame_buffer,0,sizeof(context->frame_buffer));
}

float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}