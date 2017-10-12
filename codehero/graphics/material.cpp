// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/material.h"
#include "core/texture.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/rendersystem.h"
#include "graphics/shaderprogram.h"

namespace CodeHero {

Material::Material(const std::shared_ptr<EngineContext>& iContext)
    : Serializable(iContext) {}

Material::~Material() {}

void Material::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Material);

    CH_OBJECT_ATTRIBUTE(Material, "Coordinate Offset", Vector2, Variant::Value::VVT_Vector2, nullptr, static_cast<void(Material::*)(const Vector2&)>(&Material::SetTextureCoordsOffset));
    CH_OBJECT_ATTRIBUTE(Material, "Cull Enabled", bool, Variant::Value::VVT_Bool, &Material::GetCullEnabled, &Material::SetCullEnabled);
    CH_OBJECT_ATTRIBUTE(Material, "Depth Test Enabled", bool, Variant::Value::VVT_Bool, &Material::GetDepthTest, &Material::SetDepthTest);
    CH_OBJECT_ATTRIBUTE_CAST(Material, "ShaderProgram", std::shared_ptr<Serializable>, ShaderProgram, Variant::Value::VVT_SerializablePtr, &Material::GetShaderProgram, &Material::SetShaderProgram);

    auto setTexture = [](Material* iPtr, TextureUnit iTU, const std::shared_ptr<Serializable>& iTexture) {
        auto texture = std::static_pointer_cast<Texture>(iTexture);
        CH_ASSERT(texture != nullptr);

        iPtr->SetTexture(iTU, texture);
    };
    CH_OBJECT_ATTRIBUTE_CUSTOM(Material, "Texture Diffuse", std::shared_ptr<Serializable>, Variant::Value::VVT_SerializablePtr, nullptr, [setTexture](Material* iPtr, const std::shared_ptr<Serializable>& iTexture) {
        setTexture(iPtr, TextureUnit::TU_Diffuse, iTexture);
    });
    CH_OBJECT_ATTRIBUTE_CUSTOM(Material, "Texture Specular", std::shared_ptr<Serializable>, Variant::Value::VVT_SerializablePtr, nullptr, [setTexture](Material* iPtr, const std::shared_ptr<Serializable>& iTexture) {
        setTexture(iPtr, TextureUnit::TU_Specular, iTexture);
    });
}

std::shared_ptr<Material> Material::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Material>(iContext);
}

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