// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MESH_H_
#define CODEHERO_GRAPHICS_MESH_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include "core/serializable.h"

namespace CodeHero {

// Forward declaration
class IndexBuffer;
class VertexBuffer;
class Material;
class RenderSystem;
class Bone;

class Mesh : public Serializable {
public:
    OBJECT(Mesh, Serializable)

    Mesh(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Mesh();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Mesh> Create(const std::shared_ptr<EngineContext>& iContext);

    void Draw(RenderSystem& iRS) const;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer);
    void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer);
    void SetMaterial(const std::shared_ptr<Material> iMaterial);
    void AddBone(const Bone&& iBone);

    const std::shared_ptr<VertexBuffer>& GetVertices() const { return m_pVertices; }
    const std::shared_ptr<IndexBuffer>& GetIndices() const { return m_pIndices; }
    std::shared_ptr<Material> GetMaterial() const { return m_pMaterial; }

    Bone* GetByIndex(size_t iIndex);
    Bone* GetByName(const std::string& iName);
    size_t BoneSize() const;

private:
    std::shared_ptr<VertexBuffer> m_pVertices;
    std::shared_ptr<IndexBuffer> m_pIndices;
    std::shared_ptr<Material> m_pMaterial;
    std::vector<Bone> m_Bones;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MESH_H_
