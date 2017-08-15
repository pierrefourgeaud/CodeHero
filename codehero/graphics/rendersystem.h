// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RENDERSYSTEM_H_
#define CODEHERO_CORE_RENDERSYSTEM_H_

#include <memory>
#include <vector>
#include "core/errors.h"
#include "core/math/vector2.h"
#include "core/system.h"

namespace CodeHero {

// Forward declaration
class TextureManager;
class RenderWindow;
class Shader;
class Texture;
class Matrix4;
class Vector3;
class IndexBuffer;
class VertexBuffer;
class Viewport;

enum PrimitiveType {
    PT_Points = 0,
    PT_Lines,
    PT_LineLoop,
    PT_LineStrip,
    PT_Triangles,
    PT_TriangleStrip,
    PT_TriangleFan,
    PT_Quads
};

enum Comparison {
    C_Always = 0,
    C_Equal,
    C_NotEqual,
    C_Less,
    C_LessEqual,
    C_Greater,
    C_GreaterEqual,
    C_Max
};

enum StencilOp {
    SO_Keep = 0,
    SO_Zero,
    SO_Replace,
    SO_Incr,
    SO_IncrWrap,
    SO_Decr,
    SO_DecrWrap,
    SO_Invert,
    SO_Max
};

enum BlendMode {
    BM_Zero = 0,
    BM_One,
    BM_SrcColor,
    BM_OneMinusSrcColor,
    BM_DstColor,
    BM_OneMinusDstColor,
    BM_SrcAlpha,
    BM_OneMinusSrcAlpha,
    BM_DstAlpha,
    BM_OneMinusDstAlpha,
    BM_ConstantColor,
    BM_OneMinusConstantColor,
    BM_ConstantAlpha,
    BM_OneMinusConstantAlpha
};

enum CullFace {
    CF_Front = 0,
    CF_Back
};

class RenderSystem : public System {
public:
    OBJECT(RenderSystem)

    RenderSystem(const std::shared_ptr<EngineContext>& iContext)
        : System(iContext) {}
    virtual ~RenderSystem() {}

    virtual void PollEvents() = 0;
    virtual void ClearFrameBuffer() = 0;

    void SetShaderProgramInUse(Shader* iShader) { m_pShaderProgramInUse = iShader; }
    Shader* GetShaderProgramInUse() const { return m_pShaderProgramInUse; }

    void RegisterViewport(Viewport* iViewport);

    virtual void SetShaderParameter(const std::string& iParam, int32_t iValue) = 0;
    virtual void SetShaderParameter(const std::string& iParam, float iValue) = 0;
    virtual void SetShaderParameter(const std::string& iParam, const Vector3& iVec) = 0;
    virtual void SetShaderParameter(const std::string& iParam, const Matrix4& iMat) = 0;
    virtual void SetShaderParameter(const std::string& iParam, const float* iFloat, const uint32_t iCount) = 0;
    virtual void SetVertexBuffer(const VertexBuffer& iBuffer) = 0;
    virtual void SetTexture(uint32_t iIndex, const Texture& iTexture) = 0;
    virtual void SetViewport(Viewport* iViewport) { m_pActiveViewport = iViewport; };
    virtual void SetDepthMode(Comparison iCmp) = 0;
    virtual void SetDepthTest(bool iEnabled) = 0;
    virtual void SetStencilTest(bool iEnabled) = 0;
    virtual void SetStencilMode(Comparison iMode, uint32_t iRef, uint32_t iMask) = 0;
    virtual void SetStencilWriteMask(uint32_t iMask) = 0;
    virtual void SetStencilOp(StencilOp iPass, StencilOp iFail, StencilOp iDepthFail) = 0;
    virtual void SetBlendMode(bool iEnabled, BlendMode iSrcMode, BlendMode iDstMode) = 0;
    virtual void SetCullMode(bool iEnabled, CullFace iFace = CF_Front, bool iIsCounterClockwise = true) = 0;

    virtual void SetVBO(const VertexBuffer& iBuffer) = 0;

    void SetPixelScalling(float iHorizontal, float iVertical) {
        m_PixelScalling.SetX(iHorizontal);
        m_PixelScalling.SetY(iVertical);
    }

    Vector2 GetPixelScalling() const { return m_PixelScalling; }

    virtual void Draw(PrimitiveType iType, uint32_t iVertexStart, uint32_t iVertexCount) = 0;
    // TODO(pierre) We might need to use indexStart at one point, in that case a good solution with the
    // overloading will have to be found.
    virtual void Draw(PrimitiveType iType, uint32_t iIndexCount) = 0;

    void Render();

    std::shared_ptr<RenderWindow> GetWindow() { return m_pWindow; }

    // Factory
#ifdef WIN32
#undef CreateWindow
#endif
    virtual std::shared_ptr<RenderWindow> CreateWindow(uint32_t iWidth, uint32_t iHeight) = 0;
    virtual Texture* CreateTexture() = 0;
    virtual Shader* CreateShader() = 0;
    virtual VertexBuffer* CreateVertexBuffer() = 0;
    virtual IndexBuffer* CreateIndexBuffer() = 0;

protected:
    void _SetTextureManager(TextureManager* iTextureManager) { m_pTextureManager = iTextureManager; }

    uint32_t m_BoundVBO = 0;
    std::shared_ptr<RenderWindow> m_pWindow;

private:
    TextureManager* m_pTextureManager = nullptr;

    Shader* m_pShaderProgramInUse = nullptr;
    Viewport* m_pActiveViewport = nullptr;

    std::vector<Viewport*> m_RegisteredViewports;
    
    Vector2 m_PixelScalling{1.0f, 1.0f};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RENDERSYSTEM_H_
