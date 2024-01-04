#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <glm/fwd.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Playground::Core
{
/**
 * @enum ShaderType
 * @brief enum for shader types
 * @details used to specify the type of a shader
 * @see Program
 */
enum class ShaderType
{
    Vertex = GL_VERTEX_SHADER, /** @brief vertex shader type */
    Fragment = GL_FRAGMENT_SHADER, /** @brief fragment shader type */
    Compute = GL_COMPUTE_SHADER /** @brief compute shader type */
};

class Program
{
public:
    Program() = default;
    /**
     * @brief create a program from a list of shader source code
     * @param srcs a list of pairs of shader type and source code
     */
    Program(const std::vector<std::pair<ShaderType, const std::string>> srcs);
    /**
     * @brief create a program for a compute shader
     * @param comp the source code of the compute shader
     */
    Program(const std::string &comp);

    ~Program();

    void bind();

    // getter for uniforms locations,fills the uniforms_ map and check for
    // duplicates
    void get_uniforms_locations();
    /**
     * @brief set a uniform value
     * @param name the name of the uniform
     * @param value the value to set, can be a scalar, a vector or a matrix
     */
    void set_uniform(const std::string name, const int value);
    void set_uniform(const std::string name, const float value);
    void set_uniform(const std::string name, const glm::vec2 value);
    void set_uniform(const std::string name, const glm::vec3 value);
    void set_uniform(const std::string name, const glm::vec4 value);
    void set_uniform(const std::string name, const glm::mat2 value);
    void set_uniform(const std::string name, const glm::mat3 value);
    void set_uniform(const std::string name, const glm::mat4 value);

    /**
     * getter for checking if the program is a compute shader or not
     */
    bool is_compute_shader() const
    {
        return _is_compute_shader;
    }

private:
    GLuint gl_program_;
    std::vector<GLuint> gl_shaders_;
    std::unordered_map<std::string, GLint> uniforms_;
    bool _is_compute_shader = false;
};

} // namespace Playground::Core
