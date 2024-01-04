#pragma once
#include <GL/glew.h>
#include <array>

#include "core/texture/texture.hh"

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

    FrameBuffer(FrameBuffer &&) = default;
    FrameBuffer &operator=(FrameBuffer &&) = default;

    ~FrameBuffer();

    void bind(bool clear = true, bool depth = true) const;
    void blit(bool depth = false) const;

    const glm::uvec2 &size() const;

private:
    FrameBuffer(Texture *depth, Texture **color_texture,
                size_t color_texture_count);
    GLuint gl_frame_buffer_;
    glm::uvec2 size_ = {};
};
} // namespace Playground::Core