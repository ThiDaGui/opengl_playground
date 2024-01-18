#include "core/buffer/frame_buffer.hh"

#include <GL/glew.h>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace Playground::Core
{
static GLuint create_frame_buffer_id()
{
    GLuint id = 0;
    glCreateFramebuffers(1, &id);
    return id;
}

FrameBuffer::FrameBuffer()
{}

FrameBuffer::FrameBuffer(Texture *depth)
    : FrameBuffer(depth, nullptr, 0)
{}

FrameBuffer::FrameBuffer(Texture *depth, Texture **color_textures,
                         size_t color_texture_count)
    : gl_frame_buffer_(create_frame_buffer_id())
{
    if (depth)
    {
        glNamedFramebufferTexture(gl_frame_buffer_.get(), GL_DEPTH_ATTACHMENT,
                                  depth->gl_texture_.get(), 0);
        size_ = depth->size_;
    }
    if (color_texture_count >= 8)
    {
        std::cerr << "FrameBuffer: too many color textures" << std::endl;
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < color_texture_count; ++i)
    {
        glNamedFramebufferTexture(gl_frame_buffer_.get(),
                                  GL_COLOR_ATTACHMENT0 + i,
                                  color_textures[i]->gl_texture_.get(), 0);
        size_ = color_textures[i]->size_;
    }
    const GLenum draw_buffers[] = {
        GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
        GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7
    };
    glNamedFramebufferDrawBuffers(gl_frame_buffer_.get(), color_texture_count,
                                  draw_buffers);
    if (glCheckNamedFramebufferStatus(gl_frame_buffer_.get(), GL_FRAMEBUFFER)
        != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "FrameBuffer: incomplete" << std::endl;
        exit(EXIT_FAILURE);
    }
}

FrameBuffer::~FrameBuffer()
{
    if (uint32_t handle = gl_frame_buffer_.get())
        glDeleteFramebuffers(1, &handle);
}

void FrameBuffer::bind([[maybe_unused]] bool clear,
                       [[maybe_unused]] bool depth) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, gl_frame_buffer_.get());
}

void FrameBuffer::blit(bool depth) const
{
    int32_t binding = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &binding);

    int viewport[4] = {};
    glGetIntegerv(GL_VIEWPORT, viewport);

    glBlitNamedFramebuffer(
        gl_frame_buffer_.get(), binding, 0, 0, size_.x, size_.y, 0, 0,
        viewport[2], viewport[3],
        GL_COLOR_BUFFER_BIT | (depth ? GL_DEPTH_BUFFER_BIT : 0), GL_NEAREST);
}

const glm::uvec2 &FrameBuffer::size() const
{
    return size_;
}
} // namespace Playground::Core
