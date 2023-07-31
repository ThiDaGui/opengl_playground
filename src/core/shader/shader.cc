#include "core/shader/shader.hh"

#include <cstring>
#include <iostream>

#include "utils/io/io.hh"

namespace Playground::Core
{
    Shader::Shader()
    {
        gl_program_ = glCreateProgram();
    }

    Shader::~Shader()
    {
        for (auto gl_shader : gl_shaders_)
            glDeleteShader(gl_shader);
        glDeleteProgram(gl_program_);
    }

    /**
     * Create a gl_shader, add it to gl_shaders_ and compile it
     * return true if every thing went go, otherwise false
     */

    bool Shader::add_gl_shader(const std::filesystem::path &shader_path,
                               GLenum shader_type)
    {
        GLuint gl_shader = glCreateShader(shader_type);

        GLchar *shader_source = IO::read_file(shader_path);
        int shader_length = strlen(shader_source);

        glShaderSource(gl_shader, 1, &shader_source, &shader_length);
        glCompileShader(gl_shader);

        GLsizei log_length = 0;
        glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &log_length);
        char *buff = new char[log_length + 1]();

        glGetShaderInfoLog(gl_shader, log_length + 1, nullptr, buff);

        std::cout << buff << "\n";

        GLint compile_result = GL_TRUE;
        glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &compile_result);

        if (compile_result == GL_FALSE)
            return false;

        return true;
    }

    bool Shader::link()
    {
        glLinkProgram(gl_program_);

        GLsizei log_length = 0;
        glGetProgramiv(gl_program_, GL_INFO_LOG_LENGTH, &log_length);
        char *buff = new char[log_length + 1]();

        glGetProgramInfoLog(gl_program_, log_length + 1, nullptr, buff);

        std::cout << buff << "\n";
        GLint link_result = GL_TRUE;
        glGetProgramiv(gl_program_, GL_LINK_STATUS, &link_result);

        if (link_result == GL_FALSE)
            return false;

        return true;
    }

    void Shader::use()
    {
        glUseProgram(gl_program_);
    }
} // namespace Playground::Core
