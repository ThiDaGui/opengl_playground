#include "core/mesh/mesh.hh"

#include <GL/glew.h>
#include <array>
#include <cstdint>
#include <glm/ext/vector_float3.hpp>
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

Mesh Mesh::cube(const float size)
{
    const std::vector<Vertex> vertex_buffer{
        { { size, size, size }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0 } },
        { { -size, size, size }, { 0.0, 0.0, 1.0 }, { 0.0, 1.0 } },
        { { -size, -size, size }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },
        { { size, -size, size }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0 } },

        { { -size, size, size }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0 } },
        { { size, size, size }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0 } },
        { { size, size, -size }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },
        { { -size, size, -size }, { 0.0, 1.0, 0.0 }, { 1.0, 1.0 } },

        { { -size, -size, size }, { -1.0, 0.0, 0.0 }, { 1.0, 0.0 } },
        { { -size, size, size }, { -1.0, 0.0, 0.0 }, { 0.0, 1.0 } },
        { { -size, size, -size }, { -1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
        { { -size, -size, -size }, { -1.0, 0.0, 0.0 }, { 1.0, 1.0 } },

        { { size, -size, size }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0 } },
        { { -size, -size, size }, { 0.0, -1.0, 0.0 }, { 0.0, 1.0 } },
        { { -size, -size, -size }, { 0.0, -1.0, 0.0 }, { 0.0, 0.0 } },
        { { size, -size, -size }, { 0.0, -1.0, 0.0 }, { 1.0, 1.0 } },

        { { size, size, size }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0 } },
        { { size, -size, size }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0 } },
        { { size, -size, -size }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
        { { size, size, -size }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0 } },

        { { -size, -size, -size }, { 0.0, 0.0, -1.0 }, { 1.0, 0.0 } },
        { { size, -size, -size }, { 0.0, 0.0, -1.0 }, { 0.0, 1.0 } },
        { { size, size, -size }, { 0.0, 0.0, -1.0 }, { 0.0, 0.0 } },
        { { -size, size, -size }, { 0.0, 0.0, -1.0 }, { 1.0, 1.0 } },
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

} // namespace Playground::Core
