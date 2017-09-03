// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_RENDERSYSTEMGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_RENDERSYSTEMGL_H_

#include "core/errors.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

// Forward declaration
class RenderWindow;
class Texture;
class TextureManager;
class VertexBuffer;
class IndexBuffer;

class RenderSystemGL : public RenderSystem {
public:
    RenderSystemGL(std::shared_ptr<EngineContext>& iContext);
    virtual ~RenderSystemGL() {}

    Error Initialize() override;
    void PollEvents() override;
    Error Cleanup() override;

    void ClearFrameBuffer() override;

    void SetShaderParameter(const std::string& iParam, int32_t iValue) final override;
    void SetShaderParameter(const std::string& iParam, float iValue) final override;
    void SetShaderParameter(const std::string& iParam, const Vector2& iVec) final override;
    void SetShaderParameter(const std::string& iParam, const Vector3& iVec) final override;
    void SetShaderParameter(const std::string& iParam, const Matrix4& iMat) final override;
    void SetShaderParameter(const std::string& iParam, const float* iFloat, const uint32_t iCount) final override;
    void SetVertexBuffer(const VertexBuffer& iBuffer) final override;
    void SetTexture(uint32_t iIndex, const Texture& iTexture) final override;
    void SetViewport(const std::shared_ptr<Viewport>& iViewport) final override;
    void SetDepthMode(Comparison iCmp) final override;
    void SetDepthTest(bool iEnabled) final override;
    void SetStencilTest(bool iEnabled) final override;
    void SetStencilMode(Comparison iMode, uint32_t iRef, uint32_t iMask) final override;
    void SetStencilWriteMask(uint32_t iMask) final override;
    void SetStencilOp(StencilOp iPass, StencilOp iFail, StencilOp iDepthFail) final override;
    void SetBlendMode(bool iEnabled, BlendMode iSrcMode, BlendMode iDstMode) final override;
    void SetCullMode(bool iEnabled, CullFace iFace = CF_Front, bool iIsCounterClockwise = true) final override;

    void SetVBO(const VertexBuffer& iBuffer) final override;

    void Draw(PrimitiveType iType, uint32_t iVertexStart, uint32_t iVertexCount) final override;
    void Draw(PrimitiveType iType, uint32_t iIndexCount) final override;

    // Factory
    std::shared_ptr<RenderWindow> CreateWindow(uint32_t iWidth, uint32_t iHeight) final override;
    Texture* CreateTexture() final override;
    ShaderProgram* CreateShader() final override;
    VertexBuffer* CreateVertexBuffer() final override;
    IndexBuffer* CreateIndexBuffer() final override;
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_RENDERSYSTEMGL_H_
