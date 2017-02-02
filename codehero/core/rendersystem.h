// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RENDERSYSTEM_H_
#define CODEHERO_CORE_RENDERSYSTEM_H_

#include <memory>
#include "core/errors.h"

namespace CodeHero {

// Forward declaration
class TextureManager;
class RenderWindow;
class Shader;
class Texture;
class Matrix4;
class Vector3;

class RenderSystem {
public:
    virtual ~RenderSystem() {}

    virtual Error Initialize() = 0;
    virtual void PollEvents() = 0;
    virtual Error Cleanup() = 0;

    virtual void ClearFrameBuffer() = 0;

    void SetShaderProgramInUse(Shader* iShader) { m_pShaderProgramInUse = iShader; }
    Shader* GetShaderProgramInUse() const { return m_pShaderProgramInUse; }

    virtual void SetShaderParameter(const std::string& iParam, const Vector3& iVec) = 0;
    virtual void SetShaderParameter(const std::string& iParam, const Matrix4& iMat) = 0;

    // Factory
    virtual RenderWindow* CreateWindow() = 0;
    virtual Texture* CreateTexture() = 0;
    virtual Shader* CreateShader() = 0;

protected:
    void _SetTextureManager(TextureManager* iTextureManager) { m_pTextureManager = iTextureManager; }

private:
    TextureManager* m_pTextureManager = nullptr;

    Shader* m_pShaderProgramInUse = nullptr;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RENDERSYSTEM_H_
