#include <xmmintrin.h>

typedef struct vector
{
    float x,y;
}vector_t;

vector_t point_to_screen(float point_x, float point_y, int screen_width, int screen_height);

vector_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height);

void point_to_screen_ref(vector_t* point, int screen_width, int screen_height );

void screen_to_point_ref(vector_t* screen_point, int screen_width, int screen_height);