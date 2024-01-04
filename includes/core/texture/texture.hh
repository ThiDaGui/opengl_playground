#pragma once
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

#include "core/texture/image_format.hh"

namespace Playground::Core
{

class Texture
{
public:
    Texture() = default;
    Texture(const glm::uvec2 &size, const ImageFormat format,
            const uint32_t mip_levels = 1);

    ~Texture();

    void bind(const GLuint unit = 0) const;

private:
    friend class FrameBuffer;
    GLuint gl_texture_;
    glm::uvec2 size_;
    ImageFormat format_;
};
} // namespace Playground::Core
