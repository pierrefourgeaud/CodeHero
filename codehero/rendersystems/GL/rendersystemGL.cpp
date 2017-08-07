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
#include "rendersystems/GL/shaderGL.h"
#include "rendersystems/GL/textureGL.h"
#include "rendersystems/GL/indexbufferGL.h"
#include "rendersystems/GL/vertexbufferGL.h"

namespace CodeHero {

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
        ShaderGL* shader = static_cast<ShaderGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            glUniform1i(info.location, iValue);
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, float iValue) {
    if (GetShaderProgramInUse()) {
        ShaderGL* shader = static_cast<ShaderGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            glUniform1f(info.location, iValue);
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, const Vector3& iVec) {
    if (GetShaderProgramInUse()) {
        ShaderGL* shader = static_cast<ShaderGL*>(GetShaderProgramInUse());
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
        ShaderGL* shader = static_cast<ShaderGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            glUniformMatrix4fv(info.location, 1, GL_FALSE, iMat.Data());
        }
    }
}

void RenderSystemGL::SetShaderParameter(const std::string& iParam, const float* iFloat, const uint32_t iCount) {
    if (GetShaderProgramInUse()) {
        ShaderGL* shader = static_cast<ShaderGL*>(GetShaderProgramInUse());
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
                glUniform3fv(info.location, iCount / 4, iFloat);
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

void RenderSystemGL::Draw(PrimitiveType iType, uint32_t iVertexStart, uint32_t iVertexCount) {
    glDrawArrays(iType, iVertexStart, iVertexCount);
}

void RenderSystemGL::Draw(PrimitiveType iType, uint32_t iIndexCount) {
    glDrawElements(iType, iIndexCount, GL_UNSIGNED_INT, 0);
}

// Factory
RenderWindow* RenderSystemGL::CreateWindow(uint32_t iWidth, uint32_t iHeight) {
    RenderWindow* win = new RenderWindowGL(*this);
    if (win->Create(iWidth, iHeight) != Error::OK) {
        delete win;
        win = nullptr;
    }

    LOGI << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return win;
}

Texture* RenderSystemGL::CreateTexture() {
    return new TextureGL(m_pContext);
}

Shader* RenderSystemGL::CreateShader() {
    return new ShaderGL(*this);
}

VertexBuffer* RenderSystemGL::CreateVertexBuffer() {
    return new VertexBufferGL;
}

IndexBuffer* RenderSystemGL::CreateIndexBuffer() {
    return new IndexBufferGL;
}

} // CodeHero
