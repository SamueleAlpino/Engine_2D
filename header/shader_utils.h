#include "window.h"
#include "renderer.h"

typedef enum face
{
    back  = 0,
    front = 1
}face_t;

GLuint create_program(const char* vertex_shader_name, const char* fragment_shader_name, face_t cull_face );
