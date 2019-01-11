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

vector3_t vector3_new(float x, float y, float z)
{
    vector3_t to_return = {.x = x, .y = y, .z = z};
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

vector2_t point_to_screen(float point_x, float point_y, int screen_width, int screen_height)
{
    vector2_t screen_point;
    screen_point.x = ((point_x + 1) * screen_width) / 2;

    screen_point.y = screen_height - (((point_y + 1) * screen_height) / 2);
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

vertex_t vertex_new(vector3_t position)
{
    vertex_t vertex;
    memset(&vertex, 0, sizeof(vertex_t));
    vertex.position = position;
    return vertex;
}

triangle_t triangle_new(vertex_t a, vertex_t b, vertex_t c)
{
    triangle_t triangle = {.a = a, .b = b, .c = c};
    return triangle;
}

vector2_t vector2_new(float x, float y)
{
    vector2_t to_ret = {.x = x, .y = y, .magnitude = sqrt(pow(x, 2) + pow(y, 2))};
    return to_ret;
}

float get_magnitude(vector2_t point_a, vector2_t point_b)
{
    return sqrt(pow(point_b.x - point_a.x, 2) + pow(point_b.y - point_a.y, 2));
}

float inversed_slope(float x0, float x1, float y0, float y1)
{
    return (x1 - x0) / (y1 - y0);
}

float gradient(float i, float P0, float P1)
{
    float to_return; 
    if(P0 != P1)
        return to_return = (i - P0) / (P1 - P0);

    return P0 || P1;
}

float dot_product(vector2_t a, vector2_t b)
{
    return a.x * b.x + a.y * b.y;
}

void rasterize(ctx_t *context, triangle_t *triangle)
{
    //convert point in screen space
    vector2_t vertex_a = point_to_screen(triangle->a.position.x, triangle->a.position.y, context->width, context->height);
    vector2_t vertex_b = point_to_screen(triangle->b.position.x, triangle->b.position.y, context->width, context->height);
    vector2_t vertex_c = point_to_screen(triangle->c.position.x, triangle->c.position.y, context->width, context->height);

    //order from low y to high y
    vector2_t P[3] = {vertex_a, vertex_b, vertex_c};

    vector2_t temp;

    if (P[1].y < P[0].y)
    {
        temp = P[0];
        P[0] = P[1];
        P[1] = temp;
    }

    if (P[2].y < P[1].y)
    {
        temp = P[2];
        P[2] = P[1];
        P[1] = temp;
    }

    if (P[1].y < P[0].y)
    {
        temp = P[0];
        P[0] = P[1];
        P[1] = temp;
    }

    //printf(" 0: %f 1: %f 2: %f \n ",P[0].y,P[1].y,P[2].y );

    //calculate slope to know the orientation of triangle
    int slope;

    float value_0 = inversed_slope(P[0].x, P[1].x, P[0].y, P[1].y);
    float value_1 = inversed_slope(P[0].x, P[2].x, P[0].y, P[2].y);

    //if value 0 is bigger than 1 , p0 position is right else il left
    if (value_0 > value_1)
        slope = 0;
    else
        slope = 1;

    vector2_t p_3;
    float p2_magnitude = get_magnitude(P[0], P[2]);

    vector2_t for_dot = {.x = P[2].x - P[0].x, .y = P[2].y - P[0].y};
    float dot = dot_product(P[1], for_dot);

    //projecton of P[1] on P[2] vector
    //a = dot product(a,b) / pow( magnitude (b)) * x || y
    p_3.x = (dot / pow(p2_magnitude, 2)) * P[2].x;
    p_3.y = (dot / pow(p2_magnitude, 2)) * P[2].y;

    //Debug
    // printf("magnitude P1: %f\n", p1_magnitude);
    // printf("magnitude P2: %f\n", p2_magnitude);
    // printf("x: %f  y: %f\n", p_3.x, p_3.y);

    

    for (float i = P[0].y; i < P[1].y; i++)
    {
        //calculate gradient and find X
        float gradient_pixel_p0_p1 = gradient(i, P[1].y, P[0].y);
        float lerp_value_p0_p1 = lerp(P[1].x, P[0].x, gradient_pixel_p0_p1);

        float gradient_pixel_p0_p3 = gradient(i, p_3.y, P[0].y);
        float lerp_value_p0_p3 = lerp(p_3.x, P[0].x, gradient_pixel_p0_p3);

        vector2_t pixel;
        pixel.y = i;
        pixel.x = lerp_value_p0_p1;
        put_pixel(&pixel, context,0,0,0);

        //check slope , this is in case 0
        if (slope == 0)
        {
            for (float i = lerp_value_p0_p3; i < pixel.x; i++)
            {
                vector2_t half;
                half.y = pixel.y;
                half.x = i;
                put_pixel(&half, context,0,0,255);
            }
        }
        else
        {
            for (float i = pixel.x; i < lerp_value_p0_p3; i++)
            {
                vector2_t half;
                half.y = pixel.y;
                half.x = i;
                put_pixel(&half, context,0,0,255);
            }
        }
    }

    //da p3 a p2 sulla y e da lerp y a p1 sulla x
    for (float i = P[1].y; i < P[2].y; i++)
    {
        float gradient_pixel_p1_p2 = gradient(i, P[1].y, P[2].y);
        float lerp_value_p1_p2 = lerp(P[1].x, P[2].x, gradient_pixel_p1_p2);

        float gradient_pixel_p3_p2 = gradient(i,P[2].y, p_3.y );
        float lerp_value_p3_p2 = lerp(p_3.x, P[2].x, gradient_pixel_p3_p2);
        printf("gradient:%f x0:%f  x1:%f\n",gradient_pixel_p3_p2, lerp_value_p3_p2, lerp_value_p1_p2);
        vector2_t pixel;
        pixel.y = i;
        pixel.x = lerp_value_p1_p2;
        put_pixel(&pixel, context,0,0,0);

        //check slope , this is in case 0
        if (slope == 0)
        {
            for (float i = lerp_value_p3_p2; i < pixel.x; i++)
            {
                vector2_t half;
                half.y = pixel.y;
                half.x = i;
                put_pixel(&half, context,0,0,255);
            }
        }
        else
        {
            for (float i = pixel.x; i < lerp_value_p3_p2; i++)
            {
                vector2_t half;
                half.y = pixel.y;
                half.x = i;
                put_pixel(&half, context,0,0,255);
            }
        }
    }

    //Draw wireframe
    draw_line(P[0].y, P[0].x, P[1].x, P[1].y, context);
    draw_line(P[0].y, P[0].x, P[2].x, P[2].y, context);
    draw_line(P[1].y, P[1].x, P[2].x, P[2].y, context);
    draw_line(p_3.y,P[0].x,p_3.x ,P[1].y, context);
}

void draw_line(float start_y, float start_x, float end_x, float end_y, ctx_t *ctx) //float p_0_y, float p_0_x, float p_1_y, float p_1_x,float p_2_y,float p_2_x,ctx_t* context)
{
    for (float i = start_y; i < end_y; i++)
    {
        float gradient_pixel_p0_p1 = gradient(i, end_y, start_y);

        float lerp_value = lerp(end_x, start_x, gradient_pixel_p0_p1);
        vector2_t pixel;
        pixel.y = i;
        pixel.x = lerp_value;

        put_pixel(&pixel, ctx,255,0,0);

    }
}

void put_pixel(vector2_t *vertex_pos, ctx_t *context, unsigned char R, unsigned char G, unsigned char B)
{
    //vector2_t vertex_pos = point_to_screen(vertex_pos->x,vertex_pos->y,context.width, context.height);

    if (vertex_pos->x < 0 || vertex_pos->x > context->width - 1)
        return;
    if (vertex_pos->y < 0 || vertex_pos->y > context->height - 1)
        return;

    int index = (vertex_pos->y * context->width * 4) + (vertex_pos->x * 4);
    // int backR = context->frame_buffer[index + 2];
    // int backG = context->frame_buffer[index + 1];
    // int backB = context->frame_buffer[index];
    //1 + back -> luci a intermittenza
    //BLUE
    context->frame_buffer[index] = B;
    //GREEN
    context->frame_buffer[index + 1] = G;
    //RED
    context->frame_buffer[index + 2] = R;
}

void clear_screen(ctx_t *context)
{
    memset((void *)context->frame_buffer, 0, sizeof(context->frame_buffer));
}

float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}