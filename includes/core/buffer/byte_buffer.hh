#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <cstdint>

#include "core/buffer/util.hh"

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
    GLuint gl_byte_buffer_;
    size_t byte_size_ = 0;
};
} // namespace Playground::Core
