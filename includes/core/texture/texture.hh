#pragma once

#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <type_traits>

#include "core/texture/image_format.hh"
#include "utils/GLhandle.hh"

namespace Playground::Core
{

class Texture
{
public:
    Texture() = default;
    Texture(Texture &&) = default;
    Texture &operator=(Texture &&) = default;

    ~Texture();

    Texture(const glm::uvec2 &size, const ImageFormat format,
            const uint32_t mip_levels = 1);

    void bind(const GLuint unit = 0) const;
    void bind_image(const GLuint unit, const GLint lod,
                    const AccessType access) const;

    const glm::uvec2 &size() const
    {
        return size_;
    }

private:
    friend class FrameBuffer;
    GLHandle gl_texture_ = 0;
    glm::uvec2 size_;
    ImageFormat format_;
};
} // namespace Playground::Core
