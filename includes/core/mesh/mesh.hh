#pragma once

#include <vector>

#include "core/buffer/typed_buffer.hh"
#include "core/buffer/util.hh"
#include "core/mesh/vertex.hh"

namespace Playground::Core
{
struct MeshData
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

class Mesh
{
public:
    Mesh() = default;
    Mesh(Mesh &&) = default;
    Mesh &operator=(Mesh &&) = default;

    Mesh(const MeshData &data);

    void draw() const;

private:
    TypedBuffer<Vertex> vertex_buffer_;
    TypedBuffer<uint32_t> index_buffer_;
};

} // namespace Playground::Core