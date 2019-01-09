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

vector_t point_to_screen(float point_x, float point_y, int screen_width, int screen_height)
{
    vector_t screen_point;
    screen_point.x = ((point_x + 1) * screen_width)/2;
    screen_point.y = ((point_y + 1) * screen_height)/2;
    return screen_point;
}

vector_t screen_to_point(float screen_point_x, float screen_point_y, int screen_width, int screen_height)
{
    vector_t point;

    point.x = ((screen_point_x * 2)/screen_width)-1;
    point.y = ((screen_point_y * 2)/screen_height)-1;

    return point;
}

void point_to_screen_ref(vector_t* point, int screen_width, int screen_height )
{
    point->x = (( point->x + 1) * screen_width) /2;
    point->y = (( point->y + 1) * screen_height)/2;
}

void screen_to_point_ref(vector_t* screen_point, int screen_width, int screen_height)
{
    screen_point->x = ((screen_point->x * 2)/screen_width)-1;
    screen_point->y = ((screen_point->y * 2)/screen_height)-1;
}
