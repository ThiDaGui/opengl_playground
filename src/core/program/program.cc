#include "core/program/program.hh"

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
    // init uniforms
    get_uniforms_locations();
}

Program::~Program()
{
    glDeleteProgram(gl_program_);
}

void Program::bind()
{
    glUseProgram(gl_program_);
}

void Program::get_uniforms_locations()
{
    GLint nb_uniforms = 0;
    glGetProgramiv(gl_program_, GL_ACTIVE_UNIFORMS, &nb_uniforms);
    for (GLint i = 0; i < nb_uniforms; ++i)
    {
        GLint osef = 0;
        GLenum type = 0;
        GLsizei length = 0;
        char name[1024]{};
        glGetActiveUniform(gl_program_, i, sizeof(name), &length, &osef, &type,
                           name);
        auto res = uniforms_.emplace(std::string(name),
                                     glGetUniformLocation(gl_program_, name));
        if (!res.second)
        {
            std::cerr << "Error: uniform " << name << " already exists"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void Program::set_uniform(const std::string name, const int value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniform1i(gl_program_, search->second, value);
    }
}
void Program::set_uniform(const std::string name, const float value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniform1f(gl_program_, search->second, value);
    }
}
void Program::set_uniform(const std::string name, const glm::vec2 value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniform2f(gl_program_, search->second, value.x, value.y);
    }
}
void Program::set_uniform(const std::string name, const glm::vec3 value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniform3f(gl_program_, search->second, value.x, value.y,
                           value.z);
    }
}
void Program::set_uniform(const std::string name, const glm::vec4 value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniform4f(gl_program_, search->second, value.x, value.y,
                           value.z, value.w);
    }
}
void Program::set_uniform(const std::string name, const glm::mat2 value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniformMatrix2fv(gl_program_, search->second, 1, GL_FALSE,
                                  reinterpret_cast<const GLfloat *>(&value));
    }
}
void Program::set_uniform(const std::string name, const glm::mat3 value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniformMatrix3fv(gl_program_, search->second, 1, GL_FALSE,
                                  reinterpret_cast<const GLfloat *>(&value));
    }
}
void Program::set_uniform(const std::string name, const glm::mat4 value)
{
    if (auto search = uniforms_.find(name); search != uniforms_.end())
    {
        glProgramUniformMatrix4fv(gl_program_, search->second, 1, GL_FALSE,
                                  reinterpret_cast<const GLfloat *>(&value));
    }
}

} // namespace Playground::Core
