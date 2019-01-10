#include <xmmintrin.h>
#include <string.h>

typedef struct context
{
    int width,height;
    unsigned char* frame_buffer;
}ctx_t;

typedef struct vector2
{
    float x,y;
}vector2_t;

typedef struct vector3
{   
    float x,y,z;

}vector3_t;

typedef struct vertex
{
    vector3_t position,normal,color;
    int raster_x,raster_y;  
}vertex_t;

typedef struct triangle
{
    vertex_t a,b,c;
}triangle_t;

vector3_t vector3_new(float x,float y , float z);

vertex_t vertex_new(vector3_t position);

triangle_t triangle_new(vertex_t a,vertex_t b,vertex_t c);

vector3_t vector3_zero();

vector2_t point_to_screen(float point_x, float point_y, int screen_width, int screen_height);

vector2_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height);

void point_to_screen_ref(vector2_t* point, int screen_width, int screen_height );

void screen_to_point_ref(vector2_t* screen_point, int screen_width, int screen_height);

void rasterize(ctx_t *context,triangle_t *triangle);

void put_pixel(vector2_t *vertex_pos,ctx_t *context);

void clear_screen(ctx_t *context);

float lerp(float start, float end, float gradient);