// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MATERIAL_H_
#define CODEHERO_GRAPHICS_MATERIAL_H_

#include <memory>
#include <unordered_map>
#include "core/object.h"

namespace CodeHero {

// Forward declaration
class Texture;
class ShaderProgram;
class RenderSystem;

enum TextureUnit {
    TU_Diffuse = 0,
    TU_Specular
};
using TextureUnitsMaps = std::unordered_map<TextureUnit, std::shared_ptr<Texture>>;

class Material : public Object {
public:
    OBJECT(Material)

    Material(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Material();

    // This will probably be replaced by technique when we will be able to dynamically load them
    // and when we will be supporting mulpasses
    // For the moment this will nake the current shader active and right away assign the shader parameters
    // for the texture
    void Use(RenderSystem& iRS);

    const TextureUnitsMaps& GetTextures() const { return m_Textures; }
    std::shared_ptr<Texture> GetTexture(TextureUnit iUnit) const;
    std::shared_ptr<ShaderProgram> GetShaderProgram() const { return m_pShaderProgram; }

    void SetTextures(const TextureUnitsMaps& iTextures);
    void SetTexture(TextureUnit iUnit, const std::shared_ptr<Texture>& iTexture);
    void SetShaderProgram(const std::shared_ptr<ShaderProgram>& iProgram);

    bool HasTexture(TextureUnit iUnit) const;
    bool HasShaderProgram() const { return !!m_pShaderProgram; }

private:
    TextureUnitsMaps m_Textures;
    std::shared_ptr<ShaderProgram> m_pShaderProgram;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MATERIAL_H_