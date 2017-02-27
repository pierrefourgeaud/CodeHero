// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MESH_H_
#define CODEHERO_GRAPHICS_MESH_H_

#include <memory>
#include <vector>

namespace CodeHero {

// Forward declaration
class IndexBuffer;
class VertexBuffer;

class Mesh {
public:
    Mesh();
    ~Mesh();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer);
    void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer);

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertices() const { return m_Vertices; }
    const std::vector<std::shared_ptr<IndexBuffer>>& GetIndices() const { return m_Indices; }

private:
    std::vector<std::shared_ptr<VertexBuffer>> m_Vertices;
    std::vector<std::shared_ptr<IndexBuffer>> m_Indices;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MESH_H_
