#include "core/shader/shader.hh"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "utils/io/io.hh"

namespace Playground::Core
{
    static GLuint create_shader(const ShaderType type, const std::string &src)
    {
        const GLuint shader = glCreateShader(type);

        const int len = src.size();
        const char *c_str = src.c_str();

        glShaderSource(shader, 1, &c_str, &len);
        glCompileShader(shader);

        int result = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            int len = 0;
            char log[1024]{};

            glGetShaderInfoLog(shader, sizeof(log), &len, log);
            std::cerr << log << std::endl;
            exit(EXIT_FAILURE);
        }
        return shader;
    }

    static void link_program(GLuint gl_program)
    {
        glLinkProgram(gl_program);

        int status = 0;
        glGetProgramiv(gl_program, GL_LINK_STATUS, &status);
        if (!status)
        {
            int len = 0;
            char log[1024]{};
            glGetProgramInfoLog(gl_program, sizeof(log), &len, log);
            std::cerr << log << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    Program::Program(std::vector<std::pair<ShaderType, const std::string>> srcs)
        : gl_program_(glCreateProgram())
    {
        std::vector<GLuint> shaders;
        for (std::pair<ShaderType, const std::string> &iter : srcs)
        {
            const ShaderType type = iter.first;
            const std::string &src = iter.second;

            const GLuint shader = create_shader(type, src);
            shaders.push_back(shader);

            glAttachShader(gl_program_, shader);
        }

        link_program(gl_program_);

        for (const GLuint &shader : shaders)
        {
            glDeleteShader(shader);
        }
    }

    Program::~Program()
    {
        for (auto gl_shader : gl_shaders_)
            glDeleteShader(gl_shader);
        glDeleteProgram(gl_program_);
    }

    void Program::bind()
    {
        glUseProgram(gl_program_);
    }

} // namespace Playground::Core
