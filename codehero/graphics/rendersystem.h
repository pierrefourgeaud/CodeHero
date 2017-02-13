// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RENDERSYSTEM_H_
#define CODEHERO_CORE_RENDERSYSTEM_H_

#include <memory>
#include <vector>
#include "core/errors.h"
#include "core/math/vector2.h"

namespace CodeHero {

// Forward declaration
class TextureManager;
class RenderWindow;
class Shader;
class Texture;
class Matrix4;
class Vector3;
class VertexBuffer;
class Viewport;

class RenderSystem {
public:
    virtual ~RenderSystem() {}

    virtual Error Initialize() = 0;
    virtual void PollEvents() = 0;
    virtual Error Cleanup() = 0;

    virtual void ClearFrameBuffer() = 0;

    void SetShaderProgramInUse(Shader* iShader) { m_pShaderProgramInUse = iShader; }
    Shader* GetShaderProgramInUse() const { return m_pShaderProgramInUse; }

    void RegisterViewport(Viewport* iViewport);

    virtual void SetShaderParameter(const std::string& iParam, const Vector3& iVec) = 0;
    virtual void SetShaderParameter(const std::string& iParam, const Matrix4& iMat) = 0;
    virtual void SetVertexBuffer(const VertexBuffer& iBuffer) = 0;
    virtual void SetViewport(Viewport* iViewport) { m_pActiveViewport = iViewport; };

    virtual void SetVBO(const VertexBuffer& iBuffer) = 0;

    void SetPixelScalling(float iHorizontal, float iVertical) {
        m_PixelScalling.SetX(iHorizontal);
        m_PixelScalling.SetY(iVertical);
    }

    Vector2 GetPixelScalling() const { return m_PixelScalling; }

    void Render();

    // Factory
    virtual RenderWindow* CreateWindow() = 0;
    virtual Texture* CreateTexture() = 0;
    virtual Shader* CreateShader() = 0;
    virtual VertexBuffer* CreateVertexBuffer() = 0;

protected:
    void _SetTextureManager(TextureManager* iTextureManager) { m_pTextureManager = iTextureManager; }

    uint32_t m_BoundVBO = 0;

private:
    TextureManager* m_pTextureManager = nullptr;

    Shader* m_pShaderProgramInUse = nullptr;
    Viewport* m_pActiveViewport = nullptr;

    std::vector<Viewport*> m_RegisteredViewports;
    
    Vector2 m_PixelScalling{1.0f, 1.0f};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RENDERSYSTEM_H_
