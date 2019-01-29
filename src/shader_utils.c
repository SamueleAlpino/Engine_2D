#include <shader_utils.h>

static GLuint compile_shader(GLenum shader_type, const char *file_name)
{
    SDL_RWops *rw = SDL_RWFromFile(file_name, "rb");
    if (!rw)
    {
        SDL_Log("unable to open file\n");
        exit(1);
    }

    size_t file_len = SDL_RWsize(rw);
    char *source = SDL_malloc(file_len + 1);

    if (!source)
    {
        SDL_Log("unable to allocate memory\n");
        exit(1);
    }

    if (SDL_RWread(rw, source, 1, file_len) != file_len)
    {
        SDL_Log("unable to read file\n");
        exit(1);
    }

    source[file_len] = 0;
    SDL_RWclose(rw);

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, (const GLchar **)&source, (GLint *)&file_len);

    glCompileShader(shader);

    SDL_free(source);

    GLint compile_status;
    //prima lettera definisce il tipo, iv i = int v= vettore, i[]
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLint log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char *error_log = SDL_malloc(log_size + 1);
        if (!error_log)
        {
            SDL_Log("unable to allocate memory for log \n");
            exit(1);
        }

        glGetShaderInfoLog(shader, log_size, &log_size, error_log);
        error_log[log_size] = 0;
        SDL_Log("shader compiler error %s\n", error_log);
        SDL_free(error_log);
        exit(1);
    }

    return shader;
}

GLuint create_program( const char* vertex_shader_name, const char* fragment_shader_name, face_t cull_face )
{
    GLuint program = glCreateProgram();

    glEnable(GL_DEPTH_TEST);

    if(cull_face == back)
        glCullFace(GL_BACK);
    else
        glCullFace(GL_FRONT);

    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_name);
    GLuint frag_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_name);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, frag_shader);


    glLinkProgram(program);

    glDetachShader(program, vertex_shader);
    glDetachShader(program, frag_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    glUseProgram(program);

    return program;
}


