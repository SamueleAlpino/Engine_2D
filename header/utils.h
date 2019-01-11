#include <xmmintrin.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct context
{
    int width,height;
    unsigned char* frame_buffer;
}ctx_t;

typedef struct vector2
{
    float x,y;

    float magnitude;
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

vector2_t vector2_new(float x,float y);

float get_magnitude(vector2_t point_a, vector2_t point_b);

vertex_t vertex_new(vector3_t position);

triangle_t triangle_new(vertex_t a,vertex_t b,vertex_t c);

vector3_t vector3_zero();

vector2_t point_to_screen(float point_x, float point_y, int screen_width, int screen_height);

vector2_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height);

vector2_t vector2_zero();

void point_to_screen_ref(vector2_t* point, int screen_width, int screen_height );

void screen_to_point_ref(vector2_t* screen_point, int screen_width, int screen_height);

float inversed_slope(float x0,float x1, float y0 ,float y1);

void rasterize(ctx_t *context,triangle_t *triangle);

void put_pixel(vector2_t *vertex_pos,ctx_t *context, unsigned char R, unsigned char G, unsigned char B);

void clear_screen(ctx_t *context);

float lerp(float start, float end, float gradient);

//i = x || y
float gradient(float i , float P0 , float P1 );

void draw_line(float start_y, float start_x,float end_x, float end_y, ctx_t* ctx);

float get_point_by_pitagora(vector2_t* a, vector2_t *b);

float dot_product(vector2_t a,vector2_t b);
