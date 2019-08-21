// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MATERIAL_H_
#define CODEHERO_GRAPHICS_MATERIAL_H_

#include <memory>
#include <unordered_map>

#include "core/color.h"
#include "core/math/vector2.h"
#include "core/serializable.h"
#include "core/unordered_map.h"

namespace CodeHero {

// Forward declaration
class RenderSystem;
class Technique;
class Texture;

enum TextureUnit { TU_Diffuse = 0, TU_Specular, TU_Opacity };
using TextureUnitsMaps = UnorderedMap<TextureUnit, std::shared_ptr<Texture>>;

class Material : public Serializable {
public:
    OBJECT(Material, Serializable)

    Material(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Material();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Material> Create(const std::shared_ptr<EngineContext>& iContext);

    // This will probably be replaced by technique when we will be able to dynamically load them
    // and when we will be supporting mulpasses
    // For the moment this will nake the current shader active and right away assign the shader
    // parameters for the texture
    void Use(RenderSystem& iRS);

    const TextureUnitsMaps& GetTextures() const { return m_Textures; }
    std::shared_ptr<Texture> GetTexture(TextureUnit iUnit) const;
    std::shared_ptr<Technique> GetTechnique() const { return m_pTechnique; }
    bool GetCullEnabled() const { return m_CullEnabled; }
    bool GetDepthTest() const { return m_DepthTest; }
    const Vector2& GetTextureCoordsOffset() const { return m_TextureCoordsOffset; }
    const Color& GetDiffuseColor() const { return m_DiffuseColor; }

    void SetTextures(const TextureUnitsMaps& iTextures);
    void SetTexture(TextureUnit iUnit, const std::shared_ptr<Texture>& iTexture);
    void SetTechnique(const std::shared_ptr<Technique>& iTechnique);

    void SetTextureCoordsOffset(float iXOffset, float iYOffset);
    void SetTextureCoordsOffset(const Vector2& iTextureCoordsOffset);

    void SetCullEnabled(bool iEnabled) { m_CullEnabled = iEnabled; }
    void SetDepthTest(bool iEnabled) { m_DepthTest = iEnabled; }

    void SetDiffuseColor(const Color& iColor) { m_DiffuseColor = iColor; }

    bool HasTexture(TextureUnit iUnit) const;
    bool HasTechnique() const { return !!m_pTechnique; }

private:
    TextureUnitsMaps m_Textures;
    std::shared_ptr<Technique> m_pTechnique;

    Vector2 m_TextureCoordsOffset{1, 1};

    bool m_CullEnabled = false;
    bool m_DepthTest = true;

    Color m_DiffuseColor = Color::White;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MATERIAL_H_
