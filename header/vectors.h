#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector2{
        float x, y;
        float magnitude;
} vector2_t;

typedef struct vector2_int{
        int x, y;
        float magnitude;
} vector2_int_t;

typedef struct vector3
{
    float x, y, z;

} vector3_t;

vector3_t vector3_new(float x, float y, float z);

vector3_t *vector3_p_new(float x, float y, float z);

vector2_t vector2_new(float x, float y);

float get_magnitude(vector2_int_t point_a, vector2_int_t point_b);

vector3_t vector3_zero();

vector2_t vector2_zero();

float get_point_by_pitagora(vector2_t *a, vector2_t *b);

float dot_product(vector2_int_t a, vector2_int_t b);
