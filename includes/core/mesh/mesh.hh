#pragma once

#include <sys/types.h>
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

public:
    static Mesh sphere(const unsigned int h_segments,
                       const unsigned int v_segments, const float radius);
    static Mesh cube(const float size);
    static Mesh plane(const float size);
};

} // namespace Playground::Core
