#include "vectors.h"

//from 0 to 1 , to screen space
vector2_int_t vector_to_screen(float point_x, float point_y, int screen_width, int screen_height);
vector2_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height);
void point_to_screen_ref(vector2_t *point, int screen_width, int screen_height);
void screen_to_point_ref(vector2_t *screen_point, int screen_width, int screen_height);
int point_to_screen(float point, int to_compare, int reverse);

//calculations
float inversed_slope(int x0, int x1, int y0, int y1);
float gradient(float i, float P0, float P1);
float lerp(float start, float end, float gradient);


