#include <vectors.h>

float dot_product(vector2_int_t a, vector2_int_t b)
{
    return a.x * b.x + a.y * b.y;
}

vector2_t vector2_new(float x, float y)
{
    vector2_t to_ret = {.x = x, .y = y, .magnitude = sqrt(pow(x, 2) + pow(y, 2))};
    return to_ret;
}

float get_magnitude(vector2_int_t point_a, vector2_int_t point_b)
{
    return sqrt(pow(point_b.x - point_a.x, 2) + pow(point_b.y - point_a.y, 2));
}

vector3_t vector3_new(float x, float y, float z)
{
    vector3_t to_return = {.x = x, .y = y, .z = z};
    return to_return;
}

vector3_t *vector3_p_new(float x, float y, float z)
{
    vector3_t *to_return = malloc(sizeof(vector3_t));
    to_return->x = x;
    to_return->y = y;
    to_return->z = z;

    return to_return;
}
vector3_t vector3_zero()
{
    vector3_t zero = {.x = 0, .y = 0, .z = 0};

    return zero;
    // zero.x = _mm_setzero_ps();
}

vector2_t vector2_zero()
{
    vector2_t zero = {.x = 0, .y = 0};

    return zero;
    // zero.x = _mm_setzero_ps();
}