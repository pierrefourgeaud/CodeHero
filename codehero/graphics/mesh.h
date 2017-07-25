// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MESH_H_
#define CODEHERO_GRAPHICS_MESH_H_

#include <memory>
#include <vector>
#include <unordered_map>

namespace CodeHero {

// Forward declaration
class IndexBuffer;
class VertexBuffer;
class Texture;

using TextureUnitsMaps = std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>>;

class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer);
    void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer);
    void SetTextures(const TextureUnitsMaps& iTextures);

    const std::shared_ptr<VertexBuffer>& GetVertices() const { return m_Vertices; }
    const std::shared_ptr<IndexBuffer>& GetIndices() const { return m_Indices; }
    const TextureUnitsMaps& GetTextures() const { return m_Textures; }

private:
    /*std::vector<std::shared_ptr<VertexBuffer>> m_Vertices;
    std::vector<std::shared_ptr<IndexBuffer>> m_Indices;*/
    std::shared_ptr<VertexBuffer> m_Vertices;
    std::shared_ptr<IndexBuffer> m_Indices;
    TextureUnitsMaps m_Textures;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MESH_H_
