#include "core/texture/texture_format.hh"

#include <GL/gl.h>

namespace Playground::Core
{
// from https://github.com/AlexandreLamure/OM3D/blob/main/TP/src/ImageFormat.cpp
TextureFormatGL texture_format_to_gl(TextureFormat format)
{
    switch (format)
    {
    case TextureFormat::RGBA8_UNORM:
        return TextureFormatGL{ GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE };
    case TextureFormat::RGBA8_sRGB:
        return TextureFormatGL{ GL_RGBA, GL_SRGB8_ALPHA8, GL_UNSIGNED_BYTE };
    case TextureFormat::RGB8_UNORM:
        return TextureFormatGL{ GL_RGB, GL_RGB8, GL_UNSIGNED_BYTE };
    case TextureFormat::RGB8_sRGB:
        return TextureFormatGL{ GL_RGB, GL_SRGB8, GL_UNSIGNED_BYTE };

    case TextureFormat::RGBA16_FLOAT:
        return TextureFormatGL{ GL_RGBA, GL_RGBA16F, GL_FLOAT };

    case TextureFormat::RGB16_FLOAT:
        return TextureFormatGL{ GL_RGB, GL_RGB16F, GL_FLOAT };

    case TextureFormat::Depth32_FLOAT:
        return TextureFormatGL{ GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F,
                                GL_FLOAT };
    }
}

} // namespace Playground::Core
