// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <logger.h>
#include "core/math/matrix4.h"
#include "core/math/vector3.h"
#include "rendersystems/GL/rendersystemGL.h"
#include "rendersystems/GL/renderwindowGL.h"
#include "rendersystems/GL/shaderGL.h"
#include "rendersystems/GL/textureGL.h"

namespace CodeHero {

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

void RenderSystemGL::SetShaderParameter(const std::string& iParam, const Vector3& iVec) {
    if (GetShaderProgramInUse()) {
        ShaderGL* shader = static_cast<ShaderGL*>(GetShaderProgramInUse());
        if (shader->HasParameter(iParam)) {
            const ShaderParameter& info = shader->GetParameter(iParam);

            switch (info.type) {
            case GL_FLOAT:
                glUniform1fv(info.location, 1, iVec.GetPtr());
                break;
            case GL_FLOAT_VEC2:
                glUniform2fv(info.location, 1, iVec.GetPtr());
                break;
            case GL_FLOAT_VEC3:
                glUniform3fv(info.location, 1, iVec.GetPtr());
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

            glUniformMatrix4fv(info.location, 1, GL_FALSE, iMat.GetPtr());
        }
    }
}

// Factory
RenderWindow* RenderSystemGL::CreateWindow() {
    RenderWindow* win = new RenderWindowGL();
    if (win->Create(800, 600) != Error::OK) {
        delete win;
        win = nullptr;
    }

    LOGI << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return win;
}

Texture* RenderSystemGL::CreateTexture() {
    return new TextureGL;
}

Shader* RenderSystemGL::CreateShader() {
    return new ShaderGL(*this);
}

} // CodeHero
