#include "core/buffer/util.hh"

namespace Playground::Core
{

uint32_t buffer_usage_to_gl(BufferUsage usage)
{
    switch (usage)
    {
    case BufferUsage::Attribute:
        return GL_ARRAY_BUFFER;

    case BufferUsage::Index:
        return GL_ELEMENT_ARRAY_BUFFER;

    case BufferUsage::Uniform:
        return GL_UNIFORM_BUFFER;

    case BufferUsage::Storage:
        return GL_SHADER_STORAGE_BUFFER;
    }
    return 0;
}

} // namespace Playground::Core
