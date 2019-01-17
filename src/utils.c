#include <utils.h>

int point_to_screen(float point, int to_compare, int reverse)
{
    int to_ret; 
  
    if(reverse == 0)
        to_ret =  ((point + 1) * to_compare) / 2;
    else
        to_ret = to_compare - ((point + 1) * to_compare) / 2;
   
    return to_ret;
}

vector2_int_t vector_to_screen(float point_x, float point_y, int screen_width, int screen_height)
{
    vector2_int_t screen_point;
    screen_point.x = ((point_x + 1) * screen_width) / 2;
  
    screen_point.y = (((point_y + 1) * screen_height) / 2);

  //  screen_point.int_y = screen_height - (((point_y + 1) * screen_height) / 2);
    return screen_point;
}

vector2_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height)
{
    vector2_t point;

    point.x = ((screen_point_x * 2) / screen_width) - 1;
    point.y = ((screen_point_y * 2) / screen_height) - 1;

    return point;
}

void point_to_screen_ref(vector2_t *point, int screen_width, int screen_height)
{
    point->x = ((point->x + 1) * screen_width) / 2;
    point->y = ((point->y + 1) * screen_height) / 2;
}

void screen_to_point_ref(vector2_t *screen_point, int screen_width, int screen_height)
{
    screen_point->x = ((screen_point->x * 2) / screen_width) - 1;
    screen_point->y = ((screen_point->y * 2) / screen_height) - 1;
}




float inversed_slope(int x0, int x1, int y0, int y1)
{
    return (x1 - x0) / (y1 - y0);
}

float gradient(float i, float P0, float P1)
{
    float to_return ; 
   
    if(P1 != P0)
        return to_return = (i - P0) / (P1 - P0);

    return 1;
}

float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}

