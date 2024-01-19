#include "core/texture/texture.hh"

#include <cstdint>
#include <glm/glm.hpp>

#include "core/texture/image_format.hh"

namespace Playground::Core
{

static GLuint create_texture_id()
{
    GLuint id = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    return id;
}

Texture::Texture(const glm::uvec2 &size, const ImageFormat format,
                 const uint32_t mip_levels)
    : gl_texture_(create_texture_id())
    , size_(size)
    , format_(format)
{
    const ImageFormatGL gl_format = image_format_to_gl(format);
    glTextureStorage2D(gl_texture_.get(), mip_levels, gl_format.internal_format,
                       size.x, size.y);
}

Texture::~Texture()
{
    if (uint32_t handle = gl_texture_.get())
        glDeleteTextures(1, &handle);
}

void Texture::bind(const GLuint index) const
{
    glBindTextureUnit(index, gl_texture_.get());
}

void Texture::bind_image(const GLuint unit, const ImageFormat format,
                         const AccessType access) const
{
    glBindImageTexture(unit, gl_texture_.get(), 0, GL_FALSE, 0,
                       access_type_to_gl(access),
                       image_format_to_gl(format).internal_format);
}

} // namespace Playground::Core
