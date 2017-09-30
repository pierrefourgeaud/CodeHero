// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/material.h"
#include "graphics/rendersystem.h"
#include "graphics/shaderprogram.h"
#include "core/texture.h"

namespace CodeHero {

Material::Material(const std::shared_ptr<EngineContext>& iContext)
    : Object(iContext) {}

Material::~Material() {}

void Material::Use(RenderSystem& iRS) {
    if (HasShaderProgram()) {
        // Bind the shader first, now we can bind the textures
        m_pShaderProgram->Use();

        if (HasTexture(TU_Diffuse)) {
            GetTexture(TU_Diffuse)->Bind(0);
            iRS.SetShaderParameter("material.diffuse", 0);
        }

        if (HasTexture(TU_Specular)) {
            GetTexture(TU_Specular)->Bind(1);
            iRS.SetShaderParameter("material.specular", 1);
        }

        iRS.SetShaderParameter("material.shininess", 32.0f);
        iRS.SetShaderParameter("material.textureCoordsOffset", m_TextureCoordsOffset);
    }
}

void Material::SetTextures(const TextureUnitsMaps& iTextures) {
    m_Textures = iTextures;
}

void Material::SetTexture(TextureUnit iUnit, const std::shared_ptr<Texture>& iTexture) {
    if (!iTexture) {
        // If the texture is null, let's not add it to the material
        return;
    }
    m_Textures[iUnit] = iTexture;
}

void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram>& iProgram) {
    m_pShaderProgram = iProgram;
}

void Material::SetTextureCoordsOffset(float iXOffset, float iYOffset) {
    m_TextureCoordsOffset.SetX(iXOffset);
    m_TextureCoordsOffset.SetY(iYOffset);
}

void Material::SetTextureCoordsOffset(const Vector2& iTextureCoordsOffset) {
    m_TextureCoordsOffset = iTextureCoordsOffset;
}

std::shared_ptr<Texture> Material::GetTexture(TextureUnit iUnit) const {
    auto texture = m_Textures.find(iUnit);
    if (texture == m_Textures.end()) {
        return nullptr;
    }

    return texture->second;
}

bool Material::HasTexture(TextureUnit iUnit) const {
    auto texture = m_Textures.find(iUnit);
    return texture != m_Textures.end();
}

} // namespace CodeHero