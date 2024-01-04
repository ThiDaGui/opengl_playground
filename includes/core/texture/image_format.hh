#pragma once

#include <cstdint>

namespace Playground::Core
{

enum class ImageFormat
{
    RGBA8_UNORM,
    RGBA8_sRGB,
    RGB8_UNORM,
    RGB8_sRGB,

    RGBA16_FLOAT,
    RGB16_FLOAT,
    Depth32_FLOAT,
};

struct ImageFormatGL
{
    uint32_t format;
    uint32_t internal_format;
    uint32_t component_type;
};

ImageFormatGL image_format_to_gl(ImageFormat format);

} // namespace Playground::Core
