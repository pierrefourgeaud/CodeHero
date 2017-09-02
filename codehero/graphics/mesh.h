// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MESH_H_
#define CODEHERO_GRAPHICS_MESH_H_

#include <memory>
#include <unordered_map>

namespace CodeHero {

// Forward declaration
class IndexBuffer;
class VertexBuffer;
class Material;
class RenderSystem;

class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    void Draw(RenderSystem* iRS) const;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer);
    void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer);
    void SetMaterial(const std::shared_ptr<Material> iMaterial);

    const std::shared_ptr<VertexBuffer>& GetVertices() const { return m_pVertices; }
    const std::shared_ptr<IndexBuffer>& GetIndices() const { return m_pIndices; }
    std::shared_ptr<Material> GetMaterial() const { return m_pMaterial; }

private:
    std::shared_ptr<VertexBuffer> m_pVertices;
    std::shared_ptr<IndexBuffer> m_pIndices;
    std::shared_ptr<Material> m_pMaterial;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MESH_H_
