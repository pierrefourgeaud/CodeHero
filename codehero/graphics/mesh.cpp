// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/mesh.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/bone.h"
#include "graphics/indexbuffer.h"
#include "graphics/material.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

Mesh::Mesh(const std::shared_ptr<EngineContext>& iContext) : Serializable(iContext) {}
Mesh::~Mesh() {}

void Mesh::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Mesh);

    CH_OBJECT_ATTRIBUTE_CAST(Mesh, "Material", std::shared_ptr<Serializable>, Material,
                             Variant::Value::VVT_SerializablePtr, &Mesh::GetMaterial,
                             &Mesh::SetMaterial);
}

std::shared_ptr<Mesh> Mesh::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Mesh>(iContext);
}

void Mesh::Draw(RenderSystem& iRS) const {
    m_pVertices->Use();

    if (m_pIndices && m_pIndices->GetSize() > 0) {
        m_pIndices->Use();
        iRS.Draw(PT_Triangles, m_pIndices->GetSize());
    } else {
        iRS.Draw(PT_Triangles, 0, m_pVertices->GetVertexCount());
    }
}

void Mesh::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer) {
    m_pVertices = iBuffer;
}

void Mesh::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer) {
    m_pIndices = iBuffer;
}

void Mesh::SetMaterial(const std::shared_ptr<Material> iMaterial) {
    m_pMaterial = iMaterial;
}

void Mesh::AddBone(const Bone&& iBone) {
    m_Bones.push_back(iBone);
}

Bone* Mesh::GetByIndex(size_t iIndex) {
    return iIndex < m_Bones.size() ? &m_Bones[iIndex] : nullptr;
}
size_t Mesh::BoneSize() const {
    return m_Bones.size();
}
Bone* Mesh::GetByName(const std::string& iName) {
    size_t len = m_Bones.size();
    for (size_t i = 0; i < len; ++i) {
        if (m_Bones[i].GetName() == iName) {
            return &m_Bones[i];
        }
    }

    return nullptr;
}

} // namespace CodeHero