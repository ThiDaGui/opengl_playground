#include "core/buffer/byte_buffer.hh"

#include <GL/glew.h>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace Playground::Core
{
static GLuint create_byte_buffer_id()
{
    GLuint id = 0;
    glCreateBuffers(1, &id);
    return id;
}

ByteBuffer::ByteBuffer(const void *data, size_t byte_size)
    : gl_byte_buffer_(create_byte_buffer_id())
    , byte_size_(byte_size)
{
    glNamedBufferData(gl_byte_buffer_.get(), byte_size_, data, GL_STATIC_DRAW);
}

ByteBuffer::~ByteBuffer()
{
    if (uint32_t handle = gl_byte_buffer_.get())
        glDeleteBuffers(1, &handle);
}

void ByteBuffer::bind(BufferUsage usage) const
{
    glBindBuffer(buffer_usage_to_gl(usage), gl_byte_buffer_.get());
}

void ByteBuffer::bind(BufferUsage usage, uint32_t index) const
{
    if (usage != BufferUsage::Uniform && usage != BufferUsage::Storage)
    {
        std::cerr << "Binding a buffer to an index is only supported for "
                     "uniform and storage buffers."
                  << std::endl;
        std::exit(1);
    }
    glBindBufferBase(buffer_usage_to_gl(usage), index, gl_byte_buffer_.get());
}

size_t ByteBuffer::byte_size() const
{
    return byte_size_;
}

} // namespace Playground::Core
