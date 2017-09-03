// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/batch.h"
#include "graphics/camera.h"
#include "graphics/material.h"
#include "graphics/mesh.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

void Batch::Draw(RenderSystem& iRS, const std::shared_ptr<Camera>& iCamera) {
    m_pMaterial->Use(iRS);

    // View
    iRS.SetShaderParameter("view", iCamera->GetView());
    iRS.SetShaderParameter("projection", iCamera->GetProjection());

    // Lights
    if (m_pVertexDirLights && !m_pVertexDirLights->empty()) {
        iRS.SetShaderParameter("dirLights", m_pVertexDirLights->data(), m_pVertexDirLights->size());
    }
    if (m_pVertexPointLights && !m_pVertexPointLights->empty()) {
        iRS.SetShaderParameter("pointLights", m_pVertexPointLights->data(), m_pVertexPointLights->size());
    }

    // Model
    iRS.SetShaderParameter("model", m_WorldTransform);

    // Params
    iRS.SetCullMode(m_pMaterial->GetCullEnabled());

    m_pMesh->Draw(iRS);
}

void Batch::SetMaterial(const std::shared_ptr<Material>& iMaterial) {
    m_pMaterial = iMaterial;
}

void Batch::SetMesh(const std::shared_ptr<Mesh>& iMesh) {
    m_pMesh = iMesh;
}

void Batch::SetWorldTransform(const Matrix4& iWorldTransform) {
    m_WorldTransform = iWorldTransform;
}

void Batch::SetVertexDirLights(std::vector<float>* iVertex) {
    m_pVertexDirLights = iVertex;
}

void Batch::SetVertexPointLights(std::vector<float>* iVertex) {
    m_pVertexPointLights = iVertex;
}

} // namespace CodeHero