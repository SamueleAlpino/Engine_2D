#include "utils.h"

typedef struct vertex
{
    vector3_t position, normal, color,view_position;
    int raster_x, raster_y;
} vertex_t;

typedef struct triangle
{
    vertex_t a, b, c;
} triangle_t;

typedef struct context
{
    vector3_t *camera;
    int width, height;
    unsigned char *frame_buffer;
    triangle_t *array_of_triangle;
    size_t number_of_triangle;
} ctx_t;

int append_triangle(triangle_t *value, ctx_t *ctx);
vertex_t* vertex_new(float x, float y, float z);
triangle_t* triangle_new(vertex_t* a, vertex_t* b, vertex_t* c);
ctx_t *create_ctx(int width, int height);
//Draw
void put_pixel(vector2_int_t *vertex_pos, ctx_t *context, unsigned char R, unsigned char G, unsigned char B);
void put_pixel_from_point( ctx_t *context,float x, float y, unsigned char R, unsigned char G, unsigned char B);
void draw_line(float start_y, float start_x, float end_x, float end_y, ctx_t *ctx);
void view_to_raster(ctx_t* ctx, vertex_t* vertex); 
void set_view_pos(ctx_t *ctx, triangle_t* triangle);
void rendering(ctx_t * context, int index, unsigned char R, unsigned char G, unsigned char B);
void clear_screen(ctx_t *context);
