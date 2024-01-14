#pragma once
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "core/buffer/byte_buffer.hh"
#include "core/buffer/util.hh"

namespace Playground::Core
{
template <typename T>
class TypedBuffer : public ByteBuffer
{
public:
    TypedBuffer() = default;

    TypedBuffer(std::vector<T> data)
        : TypedBuffer(data.data(), data.size())
    {}

    TypedBuffer(const T *data, size_t count)
        : ByteBuffer(data, count * sizeof(T))
    {}

    size_t element_count() const
    {
        if (byte_size() % sizeof(T) != 0)
        {
            std::cerr << "Buffer size is not a multiple of the element size."
                      << std::endl;
            std::exit(1);
        }
        return byte_size() / sizeof(T);
    }
};
} // namespace Playground::Core