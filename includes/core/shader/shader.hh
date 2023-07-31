#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <vector>

namespace Playground::Core
{

    class Shader
    {
        GLuint gl_program_;
        std::vector<GLuint> gl_shaders_;

        Shader();

        ~Shader();

        /**
         * Create a gl_shader, add it to gl_shaders_ and compile it
         * return true if every thing went go, otherwise false
         */

        bool add_gl_shader(const std::filesystem::path &shader_path,
                           GLenum shader_type);

        bool link();

        void use();
    };

} // namespace Playground::Core

