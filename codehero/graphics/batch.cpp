// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/batch.h"
#include <logger.h>
#include "graphics/camera.h"
#include "graphics/material.h"
#include "graphics/mesh.h"
#include "graphics/rendersystem.h"
#include "graphics/shaderprogram.h"
#include "graphics/technique.h"

namespace CodeHero {

void Batch::Draw(RenderSystem& iRS, const std::shared_ptr<Camera>& iCamera) {
    if (m_pMaterial->HasTechnique()) {
        auto technique = m_pMaterial->GetTechnique();
        iRS.SetBlendMode(technique->IsBlendEnabled(), technique->GetSrcBlendMode(),
                         technique->GetDstBlendMode());

        auto shaderProgram = technique->GetCachedShaderProgram();
        if (!shaderProgram) {
            auto vtxShader = technique->GetShader(Shader::T_Vertex)
                                 ->GetInstance(technique->GetShaderDefines(Shader::T_Vertex));
            auto fragShader = technique->GetShader(Shader::T_Fragment)
                                  ->GetInstance(technique->GetShaderDefines(Shader::T_Fragment));
            // TODO(pierre) Could be also cached in the RS to avoid recompilation ?
            shaderProgram = iRS.CreateShaderProgram();
            shaderProgram->Attach(vtxShader).Attach(fragShader).Link();
            technique->SetCachedShaderProgram(shaderProgram);
        }
        shaderProgram->Use();

        if (m_pMaterial->HasTexture(TU_Diffuse)) {
            m_pMaterial->GetTexture(TU_Diffuse)->Bind(0);
            iRS.SetShaderParameter("material.diffuse", 0);
        }

        if (m_pMaterial->HasTexture(TU_Specular)) {
            m_pMaterial->GetTexture(TU_Specular)->Bind(1);
            iRS.SetShaderParameter("material.specular", 1);
        }

        if (m_pMaterial->HasTexture(TU_Opacity)) {
            m_pMaterial->GetTexture(TU_Opacity)->Bind(2);
            iRS.SetShaderParameter("material.opacity", 2);
        }

        // TODO(pierre) Shininess should be a variable parameter, not a constant.
        iRS.SetShaderParameter("material.shininess", 32.0f);
        iRS.SetShaderParameter("material.textureCoordsOffset",
                               m_pMaterial->GetTextureCoordsOffset());
        iRS.SetShaderParameter("material.diffuseColor", m_pMaterial->GetDiffuseColor());
    } else {
        // TODO(pierre) Provide default technique if none was set (or set a default one
        // automatically)
        LOGW << "[Batch::Draw]: Your material does not have a technique, it is very "
             << "unlikely that the object will be rendered." << std::endl;
    }

    // View
    iRS.SetShaderParameter("view", iCamera->GetView());
    iRS.SetShaderParameter("projection", iCamera->GetProjection());

    // Lights
    if (m_pVertexDirLights && !m_pVertexDirLights->empty()) {
        iRS.SetShaderParameter("dirLights", m_pVertexDirLights->data(), m_pVertexDirLights->size());
    }
    if (m_pVertexPointLights && !m_pVertexPointLights->empty()) {
        iRS.SetShaderParameter("pointLights", m_pVertexPointLights->data(),
                               m_pVertexPointLights->size());
    }

    // Model
    iRS.SetShaderParameter("model", m_WorldTransform);

    // Params
    iRS.SetCullMode(m_pMaterial->GetCullEnabled());
    // TODO(pierre) For now both are enabled at the same time,
    // in the future we might want to differentiate them.
    iRS.SetDepthTest(m_pMaterial->GetDepthTest());
    iRS.SetDepthMask(m_pMaterial->GetDepthTest());

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

void Batch::SetDistanceFromCamera(const float& iDistanceFromCamera) {
    m_DistanceFromCamera = iDistanceFromCamera;
}

void Batch::SetVertexDirLights(std::vector<float>* iVertex) {
    m_pVertexDirLights = iVertex;
}

void Batch::SetVertexPointLights(std::vector<float>* iVertex) {
    m_pVertexPointLights = iVertex;
}

} // namespace CodeHero