#include <math.h>

typedef struct vector2{
        float x, y;
        float magnitude;
} vector2_t;

typedef struct vector3
{
    float x, y, z;
    float magnitude;

} vector3_t;

vector2_t vector2_new(float x, float y);
vector2_t vector2_zero();
vector2_t lerp_2(vector2_t start, vector2_t end, float gradient);
vector2_t vector2_normalized(vector2_t a);
vector2_t vector2_add(vector2_t a, vector2_t b);
vector2_t vector2_sub(vector2_t a, vector2_t b);
vector2_t vector2_mul(vector2_t a, float b);
float vector2_length(vector2_t a);
float vector2_dot(vector2_t a, vector2_t b);

vector3_t vector3_new(float x, float y, float z);
vector3_t vector3_zero();
vector3_t lerp_3(vector3_t start, vector3_t end, float gradient);
vector3_t vector3_normalized(vector3_t a);
vector3_t vector3_add(vector3_t a, vector3_t b);
vector3_t vector3_sub(vector3_t a, vector3_t b);
vector3_t vector3_mul(vector3_t a, float b);
vector3_t vector3_reflect(vector3_t a, vector3_t n);
vector3_t vector3_rot_y(vector3_t a, float r);
vector3_t vector3_cross(vector3_t a, vector3_t b);
float vector3_length(vector3_t a);
float vector3_dot(vector3_t a, vector3_t b);

float lerp(float start, float end, float gradient);

