#include <SDL.h>
#include <stdlib.h>
#include "rendering.h"



errno_t err;

typedef struct obj_file
{
    vertex_t* vertex_array;
    size_t vertex_array_size;
    size_t file_size;

}obj_file_t;

void parse_obj(ctx_t *context , char* data,obj_file_t* file);
void parse_obj_faces(ctx_t *context, char* data,obj_file_t* file);
char* read_file(const char* filename, size_t file_size);
char* save_faces(char* data, int index,size_t max_size);
char* save_vertex(char* data, int index);