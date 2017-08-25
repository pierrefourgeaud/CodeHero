// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <logger.h>
#include "core/math/matrix4.h"
#include "core/math/vector3.h"
#include "graphics/viewport.h"
#include "rendersystems/GL/rendersystemGL.h"
#include "rendersystems/GL/renderwindowGL.h"
#include "rendersystems/GL/shaderprogramGL.h"
#include "rendersystems/GL/textureGL.h"
#include "rendersystems/GL/indexbufferGL.h"
#include "rendersystems/GL/vertexbufferGL.h"

namespace CodeHero {

static const uint32_t glComparison[] = {
    GL_ALWAYS,
    GL_EQUAL,
    GL_NOTEQUAL,
    GL_LESS,
    GL_LEQUAL,
    GL_GREATER,
    GL_GEQUAL
};

static const uint32_t glStencilOps[] = {
    GL_KEEP,
    GL_ZERO,
    GL_REPLACE,
    GL_INCR,
    GL_INCR_WRAP,
    GL_DECR,
    GL_DECR_WRAP,
    GL_INVERT
};

static const uint32_t glBlendMode[] = {
    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_CONSTANT_COLOR,
    GL_ONE_MINUS_CONSTANT_COLOR,
    GL_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_ALPHA
};

static const uint32_t glCullFaces[] = {
    GL_FRONT,
    GL_BACK
};

RenderSystemGL::RenderSystemGL(std::shared_ptr<EngineContext>& iContext)
    : RenderSystem(iContext) {}

Error RenderSystemGL::Initialize() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return Error::OK;
}

void RenderSystemGL::PollEvents() {
    glfwPollEvents();
}

Error RenderSystemGL::Cleanup() {
    glfwTerminate();
    return Error::OK;
}

void RenderSystemGL::ClearFrameBuffer() {
    // Background Fill Color
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, int32_t iValue) {
    if (GetShaderProgramInUse()) {
        ShaderProgramGL* shader = static_cast<ShaderProgramGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            glUniform1i(info.location, iValue);
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, float iValue) {
    if (GetShaderProgramInUse()) {
        ShaderProgramGL* shader = static_cast<ShaderProgramGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            glUniform1f(info.location, iValue);
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, const Vector3& iVec) {
    if (GetShaderProgramInUse()) {
        ShaderProgramGL* shader = static_cast<ShaderProgramGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            switch (info.type) {
            case GL_FLOAT:
                glUniform1fv(info.location, 1, iVec.Data());
                break;
            case GL_FLOAT_VEC2:
                glUniform2fv(info.location, 1, iVec.Data());
                break;
            case GL_FLOAT_VEC3:
                glUniform3fv(info.location, 1, iVec.Data());
                break;
            default: break;
            }
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, const Matrix4& iMat) {
    if (GetShaderProgramInUse()) {
        ShaderProgramGL* shader = static_cast<ShaderProgramGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            glUniformMatrix4fv(info.location, 1, GL_FALSE, iMat.Data());
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, const float* iFloat, const uint32_t iCount) {
    if (GetShaderProgramInUse()) {
        ShaderProgramGL* shader = static_cast<ShaderProgramGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            switch (info.type) {
            case GL_FLOAT:
                glUniform1fv(info.location, iCount, iFloat);
                break;
            case GL_FLOAT_VEC2:
                glUniform2fv(info.location, iCount / 2, iFloat);
                break;
            case GL_FLOAT_VEC3:
                glUniform3fv(info.location, iCount / 3, iFloat);
                break;
            case GL_FLOAT_VEC4:
                glUniform4fv(info.location, iCount / 4, iFloat);
                break;
            case GL_FLOAT_MAT3:
                glUniformMatrix3fv(info.location, iCount / 9, GL_FALSE, iFloat);
                break;
            default: break;
            }
        }
    }
}

void RenderSystemGL::SetVertexBuffer(const VertexBuffer& iBuffer) {
    SetVBO(iBuffer);

    uint32_t vertexSize = iBuffer.GetVertexSize();

    for (uint32_t i = 0; i < VertexBuffer::EL_Max; ++i) {
        uint32_t bit = 1 << i;
        if (iBuffer.IsBitActive(bit)) {
            glVertexAttribPointer(
                i,
                VertexBufferGL::ElementComponents[i],
                VertexBufferGL::ElementType[i],
                GL_FALSE, // ?
                vertexSize,
                reinterpret_cast<GLvoid*>(iBuffer.GetElementOffset(i)));
            glEnableVertexAttribArray(i);
        }
    }
}

void RenderSystemGL::SetTexture(uint32_t iIndex, const Texture& iTexture) {
    glActiveTexture(GL_TEXTURE0 + iIndex);
    glBindTexture(GL_TEXTURE_2D, iTexture.GetGPUObject().intHandle);
}

void RenderSystemGL::SetVBO(const VertexBuffer& iBuffer) {
    if (m_BoundVBO != iBuffer.GetGPUObject().intHandle) {
        glBindBuffer(GL_ARRAY_BUFFER, iBuffer.GetGPUObject().intHandle);
        m_BoundVBO = iBuffer.GetGPUObject().intHandle;
    }
}

void RenderSystemGL::SetViewport(Viewport* iViewport) {
    RenderSystem::SetViewport(iViewport);

    Vector2 scalling = GetPixelScalling();
    glViewport(iViewport->x() * scalling.x(),
               iViewport->y() * scalling.y(),
               iViewport->width() * scalling.x(),
               iViewport->height() * scalling.y());
}

void RenderSystemGL::SetDepthMode(Comparison iCmp) {
    // TODO(pierre) Cache the cmp mode
    glDepthFunc(glComparison[iCmp]);
}

void RenderSystemGL::SetDepthTest(bool iEnabled) {
    // TODO(pierre) Maybe cache the value of the depth mask.
    glDepthMask(iEnabled ? GL_TRUE : GL_FALSE);
}

void RenderSystemGL::SetStencilTest(bool iEnabled) {
    // TODO(pierre) Maybe we should cache the value of enable ?
    if (iEnabled) {
        glEnable(GL_STENCIL_TEST);
    } else {
        glDisable(GL_STENCIL_TEST);
    }
}

void RenderSystemGL::SetStencilMode(Comparison iMode, uint32_t iRef, uint32_t iMask) {
    // TODO(pierre) We should probably cache again the 3 args
    glStencilFunc(glComparison[iMode], iRef, iMask);
}

void RenderSystemGL::SetStencilWriteMask(uint32_t iMask) {
    // TODO(pierre) We should probably cache again the 3 args
    glStencilMask(iMask);
}

void RenderSystemGL::SetStencilOp(StencilOp iPass, StencilOp iFail, StencilOp iDepthFail) {
    // TODO(pierre) We should probably cache the 3 pass args
    glStencilOp(glStencilOps[iFail], glStencilOps[iDepthFail], glStencilOps[iPass]);
}

void RenderSystemGL::SetBlendMode(bool iEnabled, BlendMode iSrcMode, BlendMode iDstMode) {
    // TODO(pierre) We should probably cache the enable/disable and the modes ?
    if (iEnabled) {
        glEnable(GL_BLEND);
        glBlendFunc(glBlendMode[iSrcMode], glBlendMode[iDstMode]);
    } else {
        glDisable(GL_BLEND);
    }
    // TODO(pierre) Should we do something for the glBlendEquation and the glBlendFuncSeparate ?
}

void RenderSystemGL::SetCullMode(bool iEnabled, CullFace iFace /* = CF_Front */, bool iIsCounterClockwise /* = true */) {
    // TODO(pierre) Should we cache the values ?
    if (iEnabled) {
        glEnable(GL_CULL_FACE);
        glCullFace(glCullFaces[iFace]);
        glFrontFace(iIsCounterClockwise ? GL_CCW : GL_CW);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

void RenderSystemGL::Draw(PrimitiveType iType, uint32_t iVertexStart, uint32_t iVertexCount) {
    glDrawArrays(iType, iVertexStart, iVertexCount);
}

void RenderSystemGL::Draw(PrimitiveType iType, uint32_t iIndexCount) {
    glDrawElements(iType, iIndexCount, GL_UNSIGNED_INT, 0);
}

// Factory
std::shared_ptr<RenderWindow> RenderSystemGL::CreateWindow(uint32_t iWidth, uint32_t iHeight) {
    m_pWindow.reset(new RenderWindowGL(*this));
    if (m_pWindow->Create(iWidth, iHeight) != Error::OK) {
        m_pWindow.reset();
    }

    LOGI << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return m_pWindow;
}

Texture* RenderSystemGL::CreateTexture() {
    return new TextureGL(m_pContext);
}

ShaderProgram* RenderSystemGL::CreateShader() {
    return new ShaderProgramGL(*this);
}

VertexBuffer* RenderSystemGL::CreateVertexBuffer() {
    return new VertexBufferGL;
}

IndexBuffer* RenderSystemGL::CreateIndexBuffer() {
    return new IndexBufferGL;
}

} // CodeHero
