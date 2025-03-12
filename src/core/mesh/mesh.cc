#include "core/mesh/mesh.hh"

#include <GL/glew.h>
#include <array>
#include <cmath>
#include <cstdint>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

#include "core/mesh/vertex.hh"

namespace Playground::Core
{
Mesh::Mesh(const MeshData &data)
    : vertex_buffer_(data.vertices)
    , index_buffer_(data.indices)
{}

void Mesh::draw() const
{
    vertex_buffer_.bind(BufferUsage::Attribute);
    index_buffer_.bind(BufferUsage::Index);

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    // vertex normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<const void *>(3 * sizeof(float)));

    // vertex uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<const void *>(6 * sizeof(float)));

    // vertex color
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<const void *>(8 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glDrawElements(GL_TRIANGLES, index_buffer_.element_count(), GL_UNSIGNED_INT,
                   nullptr);
}

// notation: latitude/longitude/radius
// https://fr.wikipedia.org/wiki/Coordonn%C3%A9es_sph%C3%A9riques#Convention_rayon-longitude-latitude
[[maybe_unused]] static glm::vec3
spherical_to_cartesian(const float theta, const float delta, const float radius)
{
    return glm::vec3{
        radius * std::cos(delta) * std::cos(theta),
        radius * std::cos(delta) * std::sin(theta),
        radius * std::sin(delta),
    };
}

Mesh Mesh::sphere([[maybe_unused]] const uint32_t h_segments,
                  [[maybe_unused]] const uint32_t v_segments,
                  [[maybe_unused]] const float radius,
                  [[maybe_unused]] const glm::vec4 color)
{
    std::vector<Vertex> vertex_buffer{};
    std::vector<uint32_t> indices{};

    for (uint32_t i_theta = 0; i_theta <= h_segments; i_theta++)
    {
    }

    return Mesh(MeshData{ vertex_buffer, indices });
}

Mesh Mesh::cube(const float size, const glm::vec4 color)
{
    const std::vector<Vertex> vertex_buffer{
        { { size / 2.0f, size / 2.0f, size / 2.0f },
          { 0.0, 0.0, 1.0 },
          { 1.0, 1.0 },
          color },
        { { -size / 2.0f, size / 2.0f, size / 2.0f },
          { 0.0, 0.0, 1.0 },
          { 0.0, 1.0 },
          color },
        { { -size / 2.0f, -size / 2.0f, size / 2.0f },
          { 0.0, 0.0, 1.0 },
          { 0.0, 0.0 },
          color },
        { { size / 2.0f, -size / 2.0f, size / 2.0f },
          { 0.0, 0.0, 1.0 },
          { 1.0, 0.0 },
          color },

        { { -size / 2.0f, size / 2.0f, size / 2.0f },
          { 0.0, 1.0, 0.0 },
          { 1.0, 0.0 },
          color },
        { { size / 2.0f, size / 2.0f, size / 2.0f },
          { 0.0, 1.0, 0.0 },
          { 0.0, 1.0 },
          color },
        { { size / 2.0f, size / 2.0f, -size / 2.0f },
          { 0.0, 1.0, 0.0 },
          { 0.0, 0.0 },
          color },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f },
          { 0.0, 1.0, 0.0 },
          { 1.0, 1.0 },
          color },

        { { -size / 2.0f, -size / 2.0f, size / 2.0f },
          { -1.0, 0.0, 0.0 },
          { 1.0, 0.0 },
          color },
        { { -size / 2.0f, size / 2.0f, size / 2.0f },
          { -1.0, 0.0, 0.0 },
          { 0.0, 1.0 },
          color },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f },
          { -1.0, 0.0, 0.0 },
          { 0.0, 0.0 },
          color },
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f },
          { -1.0, 0.0, 0.0 },
          { 1.0, 1.0 },
          color },

        { { size / 2.0f, -size / 2.0f, size / 2.0f },
          { 0.0, -1.0, 0.0 },
          { 1.0, 0.0 },
          color },
        { { -size / 2.0f, -size / 2.0f, size / 2.0f },
          { 0.0, -1.0, 0.0 },
          { 0.0, 1.0 },
          color },
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f },
          { 0.0, -1.0, 0.0 },
          { 0.0, 0.0 },
          color },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f },
          { 0.0, -1.0, 0.0 },
          { 1.0, 1.0 },
          color },

        { { size / 2.0f, size / 2.0f, size / 2.0f },
          { 1.0, 0.0, 0.0 },
          { 1.0, 0.0 },
          color },
        { { size / 2.0f, -size / 2.0f, size / 2.0f },
          { 1.0, 0.0, 0.0 },
          { 0.0, 1.0 },
          color },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f },
          { 1.0, 0.0, 0.0 },
          { 0.0, 0.0 },
          color },
        { { size / 2.0f, size / 2.0f, -size / 2.0f },
          { 1.0, 0.0, 0.0 },
          { 1.0, 1.0 },
          color },

        { { -size / 2.0f, -size / 2.0f, -size / 2.0f },
          { 0.0, 0.0, -1.0 },
          { 1.0, 0.0 },
          color },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f },
          { 0.0, 0.0, -1.0 },
          { 0.0, 1.0 },
          color },
        { { size / 2.0f, size / 2.0f, -size / 2.0f },
          { 0.0, 0.0, -1.0 },
          { 0.0, 0.0 },
          color },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f },
          { 0.0, 0.0, -1.0 },
          { 1.0, 1.0 },
          color },
    };

    std::vector<uint32_t> indices{
        0,  1,  2, //
        0,  2,  3, //
        4,  5,  6, //
        4,  6,  7, //
        8,  9,  10, //
        8,  10, 11, //
        12, 13, 14, //
        12, 14, 15, //
        16, 17, 18, //
        16, 18, 19, //
        20, 21, 22, //
        20, 22, 23, //
    };

    return Mesh{ MeshData{ vertex_buffer, indices } };
}

Mesh Mesh::plane(const float size, const glm::vec4 color)
{
    const std::vector<Vertex> vertex_buffer{
        { { size / 2.0f, size / 2.0f, 0.0f },
          { 0.0, 0.0, 1.0 },
          { 1.0, 1.0 },
          color },
        { { -size / 2.0f, size / 2.0f, 0.0f },
          { 0.0, 0.0, 1.0 },
          { 0.0, 1.0 },
          color },
        { { -size / 2.0f, -size / 2.0f, 0.0f },
          { 0.0, 0.0, 1.0 },
          { 0.0, 0.0 },
          color },
        { { size / 2.0f, -size / 2.0f, 0.0f },
          { 0.0, 0.0, 1.0 },
          { 1.0, 0.0 },
          color }
    };

    const std::vector<uint32_t> indices{
        0, 1, 2, //
        0, 2, 3, //
    };

    return Mesh(MeshData{ vertex_buffer, indices });
}

} // namespace Playground::Core
