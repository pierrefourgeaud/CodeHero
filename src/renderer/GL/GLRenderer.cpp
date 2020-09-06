// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/GLRenderer.h"

#include "core/logger/Logger.h"
#include "renderer/GL/GLPlatform.h"
#include "renderer/GL/GLUtils.h"
#include "renderer/GL/GLWindow.h"
#include "renderer/GL/HAL/GLApi.h"

namespace CodeHero {

bool GLRenderer::Initialize() {
    if (!GLInit()) {
        LOGE << "Failed to initialize GLFW. Quitting.";
        return false;
    }

    return true;
}

bool GLRenderer::Cleanup() {
    GLTerminate();
    return true;
}

void GLRenderer::PollEvents() {}

void GLRenderer::Draw() {}

void GLRenderer::SetViewport(uint32_t iX, uint32_t iY, uint32_t iWidth, uint32_t iHeight) {
    GL_CALL(glViewport(iX, iY, iWidth, iHeight));
}

std::shared_ptr<Window> GLRenderer::MakeWindow(uint32_t iWidth, uint32_t iHeight) {
    auto window = std::make_shared<GLWindow>();
    if (window->Create(iWidth, iHeight)) {
        return window;
    }

    return nullptr;
}

} // namespace CodeHero