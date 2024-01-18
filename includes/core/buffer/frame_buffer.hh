#pragma once
#include <GL/glew.h>
#include <array>

#include "core/texture/texture.hh"
#include "utils/GLhandle.hh"

namespace Playground::Core
{
class FrameBuffer
{
public:
    template <size_t N>
    FrameBuffer(Texture *depth, std::array<Texture *, N> color_textures)
        : FrameBuffer(depth, color_textures.data(), color_textures.size())
    {}

    FrameBuffer();
    FrameBuffer(Texture *depth);

    FrameBuffer(FrameBuffer &&other) = default;

    FrameBuffer &operator=(FrameBuffer &&other) = default;

    void swap(FrameBuffer &other)
    {
        std::swap(gl_frame_buffer_, other.gl_frame_buffer_);
        std::swap(size_, other.size_);
    }

    ~FrameBuffer();

    void bind(bool clear = true, bool depth = true) const;
    void blit(bool depth = false) const;

    const glm::uvec2 &size() const;

private:
    FrameBuffer(Texture *depth, Texture **color_texture,
                size_t color_texture_count);
    GLHandle gl_frame_buffer_ = 0;
    glm::uvec2 size_ = {};
};
} // namespace Playground::Core
