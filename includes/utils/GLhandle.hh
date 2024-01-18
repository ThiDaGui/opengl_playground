#pragma once

#include <cstdint>
#include <variant>

class GLHandle
{
public:
    GLHandle() = default;
    GLHandle(uint32_t handle)
        : handle_(handle)
    {}

    GLHandle(GLHandle &&other)
    {
        std::swap(handle_, other.handle_);
    }

    GLHandle &operator=(GLHandle &&other)
    {
        std::swap(handle_, other.handle_);
        return *this;
    }

    uint32_t get() const
    {
        return handle_;
    }

    bool is_valid() const
    {
        return handle_ != 0;
    }

private:
    uint32_t handle_ = 0;
};
