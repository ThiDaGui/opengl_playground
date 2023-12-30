#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <glm/fwd.hpp>
#include <string>
#include <utility>
#include <vector>

namespace Playground::Core
{
    enum ShaderType
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    class Program
    {
    public:
        Program() = default;
        Program(
            const std::vector<std::pair<ShaderType, const std::string>> srcs);

        ~Program();

        void bind();

        void set_uniform(const std::string name, const int value);
        void set_uniform(const std::string name, const float value);
        void set_uniform(const std::string name, const glm::vec2 value);
        void set_uniform(const std::string name, const glm::vec3 value);
        void set_uniform(const std::string name, const glm::vec4 value);
        void set_uniform(const std::string name, const glm::mat4 value);

    private:
        GLuint gl_program_;
        std::vector<GLuint> gl_shaders_;
    };

} // namespace Playground::Core

