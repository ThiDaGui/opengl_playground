#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <cstdint>

#include "core/buffer/util.hh"
#include "utils/GLhandle.hh"

namespace Playground::Core
{
class ByteBuffer
{
public:
    ByteBuffer() = default;
    ByteBuffer(ByteBuffer &&) = default;
    ByteBuffer &operator=(ByteBuffer &&) = default;

    ByteBuffer(const void *data, size_t byte_size);

    ~ByteBuffer();

    void bind(BufferUsage usage) const;
    void bind(BufferUsage usage, uint32_t index) const;

    size_t byte_size() const;

private:
    GLHandle gl_byte_buffer_ = 0;
    size_t byte_size_ = 0;
};
} // namespace Playground::Core
