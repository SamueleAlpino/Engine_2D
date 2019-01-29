#include <vectors.h>

#pragma region vector2

vector2_t vector2_new(float x, float y)
{
    vector2_t to_ret = {.x = x, .y = y, .magnitude = sqrt(pow(x, 2) + pow(y, 2))};
    return to_ret;
}

vector2_t vector2_zero()
{
    vector2_t zero = {.x = 0, .y = 0};

    return zero;
}

vector2_t lerp_2(vector2_t start, vector2_t end, float gradient)
{
    vector2_t v;
    v.x = lerp(start.x, end.x, gradient);
    v.y = lerp(start.y, end.y, gradient);
    return v;
}

vector2_t vector2_normalized(vector2_t a)
{
    float length = 1.0 / vector2_length(a);
    return vector2_mul(a, length);
}

vector2_t vector2_sub(vector2_t a, vector2_t b)
{
    vector2_t v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    return v;
}

vector2_t vector2_add(vector2_t a, vector2_t b)
{
    vector2_t v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    return v;
}

vector2_t vector2_mul(vector2_t a, float b)
{
    vector2_t v;
    v.x = a.x * b;
    v.y = a.y * b;
    return v;
}

float vector2_dot(vector2_t a, vector2_t b)
{
    return a.x * b.x + a.y * b.y;
}


float vector2_length(vector2_t a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

#pragma endregion

//----------------------------------------------------

#pragma region vector3

vector3_t vector3_new(float x, float y, float z)
{
    vector3_t to_return = {.x = x, .y = y, .z = z};
    return to_return;
}

vector3_t vector3_zero()
{
    vector3_t zero = {.x = 0, .y = 0, .z = 0};
    return zero;
}

vector3_t lerp_3(vector3_t start, vector3_t end, float gradient)
{
    vector3_t v;
    v.x = lerp(start.x, end.x, gradient);
    v.y = lerp(start.y, end.y, gradient);
    v.z = lerp(start.z, end.z, gradient);
    return v;
}

vector3_t vector3_normalized(vector3_t a)
{
    float length = 1.0 / vector3_length(a);
    return vector3_mul(a, length);
}

vector3_t vector3_mul(vector3_t a, float b)
{
    vector3_t v;
    v.x = a.x * b;
    v.y = a.y * b;
    v.z = a.z * b;
    return v;
}

vector3_t vector3_sub(vector3_t a, vector3_t b)
{
    vector3_t v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;

    return v;
}

vector3_t vector3_add(vector3_t a, vector3_t b)
{
    vector3_t v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;

    return v;
}

vector3_t vector3_cross(vector3_t a, vector3_t b)
{
    return vector3_new(a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x);
}

vector3_t vector3_rot_y(vector3_t a, float r)
{
    vector3_t v;
    v.x = cosf(r) * a.x - sinf(r) * a.z;
    v.y = a.y;
    v.z = sinf(r) * a.x + cosf(r) * a.z;
    return v;
}

vector3_t vector3_reflect(vector3_t a, vector3_t n)
{
    float dot2  = vector3_dot(a, n) * 2;
    vector3_t v = vector3_mul(n, dot2);
    return vector3_sub(a, v);
}


float vector3_length(vector3_t a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}


float vector3_dot(vector3_t a, vector3_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

#pragma endregion

//----------------------------------------------------

float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}

