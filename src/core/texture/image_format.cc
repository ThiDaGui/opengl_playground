#include <GL/gl.h>

#include "core/texture/image_format.hh"

namespace Playground::Core
{
// from https://github.com/AlexandreLamure/OM3D/blob/main/TP/src/ImageFormat.cpp
ImageFormatGL image_format_to_gl(ImageFormat format)
{
    switch (format)
    {
    case ImageFormat::RGBA8_UNORM:
        return ImageFormatGL{ GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE };
    case ImageFormat::RGBA8_sRGB:
        return ImageFormatGL{ GL_RGBA, GL_SRGB8_ALPHA8, GL_UNSIGNED_BYTE };
    case ImageFormat::RGB8_UNORM:
        return ImageFormatGL{ GL_RGB, GL_RGB8, GL_UNSIGNED_BYTE };
    case ImageFormat::RGB8_sRGB:
        return ImageFormatGL{ GL_RGB, GL_SRGB8, GL_UNSIGNED_BYTE };

    case ImageFormat::RGBA16_FLOAT:
        return ImageFormatGL{ GL_RGBA, GL_RGBA16F, GL_FLOAT };

    case ImageFormat::RGB16_FLOAT:
        return ImageFormatGL{ GL_RGB, GL_RGB16F, GL_FLOAT };

    case ImageFormat::Depth32_FLOAT:
        return ImageFormatGL{ GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F,
                              GL_FLOAT };
    }
}

} // namespace Playground::Core
