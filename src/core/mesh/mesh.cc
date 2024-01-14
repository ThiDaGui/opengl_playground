#include "core/mesh/mesh.hh"

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>

namespace Playground::Core
{
Mesh::Mesh(const MeshData &data)
    : vertex_buffer_(data.vertices.data(), data.vertices.size())
    , index_buffer_(data.indices.data(), data.indices.size())
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
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<const void *>(8 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glDrawElements(GL_TRIANGLES, index_buffer_.element_count(), GL_UNSIGNED_INT,
                   nullptr);
}

} // namespace Playground::Core