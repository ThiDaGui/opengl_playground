#pragma once
#include <GL/gl.h>
#include <cstdint>

namespace Playground::Core
{
enum class BufferUsage
{
    Attribute,
    Index,
    Uniform,
    Storage,
};

uint32_t buffer_usage_to_gl(BufferUsage usage);

} // namespace Playground::Core
