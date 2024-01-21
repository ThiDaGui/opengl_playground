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
    glTextureParameteri(gl_texture_.get(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(gl_texture_.get(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(gl_texture_.get(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(gl_texture_.get(), GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST);
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

void Texture::bind_image(const GLuint unit, const GLint lod,
                         const AccessType access) const
{
    glBindImageTexture(unit, gl_texture_.get(), lod, GL_FALSE, 0,
                       access_type_to_gl(access),
                       image_format_to_gl(format_).internal_format);
}

} // namespace Playground::Core
