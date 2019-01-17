#include <obj_parser.h>

char* save_vertex(char* data, int index)
{
    if(data[index] == 'v')
        index += 2;
    
    char* vertex  = NULL;
    size_t length = 0;
    
    while(!SDL_isspace(data[index]) && data[index] != 'v' && data[index] != '\n')
    {
        length++;
        vertex = realloc(vertex,length);       
        vertex[length - 1] = data[index];
        index += 1;        
    }   

    if( data[index] == '\n')
    {
        length++;
        vertex = realloc(vertex,length);       
        vertex[length-1] = 0;
        return vertex;
    }   
    else if(SDL_isspace(data[index]))
    {
        length++;
        vertex = realloc(vertex,length);       
        vertex[length-1]=0;
        index += 1;
        return vertex;
    }
    
    return vertex;
}

char* save_faces(char* data, int index, size_t max_size)
{
    if(data[index] == 'f')
        index+=2;

    char* face       = NULL;
    size_t length = 0;
    
    while(data[index] != '/' && index <= max_size)
    {
        length++;
        face=realloc(face,length);
        face[length-1] = data[index];
        index += 1;
    }
  
    if(data[index] == '/')
    {
        length++;
        face = realloc(face,length);       
        face[length - 1 ] = 0; 
        while(!SDL_isspace(data[index]) && data[index] != 'f' && index <= max_size)
        {
            index+=1;
        }

        if(SDL_isspace(data[index]) && index <= max_size)
            index += 1;
        else if(data[index] =='f'&& index <= max_size)
            index -= 1;

        return face;
    }
    return face;
}

char* read_file(const char* filename, size_t file_size)
{
    FILE *file_reader =fopen(filename,"rb");
    // FILE *file_reader = NULL;
    // if((err = fopen_s(&file_reader,filename,"r")) != 0)
    // {
    //     printf("Read Error");
    //     return NULL;
    // }

    if(!file_reader)
    {
        printf("Read Error");
        return NULL;
    }

    fseek(file_reader,0,SEEK_END);
    printf("pointer %p\n",file_reader);
    file_size = ftell(file_reader);

    fseek(file_reader,0,SEEK_SET);

    char *data = malloc(file_size);

    if(!data)
    {
        fclose(file_reader);
        printf("Data null");
        return NULL;
    }

    fread (data,1,file_size,file_reader);
    fclose(file_reader);
    return data;
}

void parse_obj(ctx_t *context , char* data,obj_file_t* file)
{
    for(int i = 0;i < file->file_size;i++)
    {
        if(data[i]=='v')
        {
            if( data[ i + 1 ]=='t' || data[ i + 1 ] == 'n')
                return;

            char* x= save_vertex(data,i);
            char* y= save_vertex(data,i);
            char* z= save_vertex(data,i);            
           
            file->vertex_array_size++;
            file->vertex_array = realloc(file->vertex_array,sizeof(vertex_t)* file->vertex_array_size);
            vertex_t *vertex = vertex_new((float)atof(x),(float)atof(y),(float)atof(z));
            file->vertex_array[file->vertex_array_size-1] =* vertex;
        }
    }
}

void parse_obj_faces(ctx_t *context, char* data,obj_file_t* file)
{
    for(int i=0;i<file->file_size;i++)
    {
        if(data[i]=='f')
        {   
            char* index1 = save_faces(data,i,file->file_size);
            char* index2 = save_faces(data,i,file->file_size);
            char* index3 = save_faces(data,i,file->file_size);         
            
            triangle_t *triangle=triangle_new( &file->vertex_array[atoi(index1)-1],&file->vertex_array[atoi(index2)-1],&file->vertex_array[atoi(index3)-1]);
            
            append_triangle(triangle, context);
        }
    }
}


