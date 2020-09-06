// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/GLWindow.h"

#include "core/ModuleManager.h"
#include "core/String.h"
#include "core/logger/Logger.h"
#include "platform/IPlatformWindow.h"
#include "platform/PlatformModule.h"
#include "platform/PlatformWindowParams.h"
#include "renderer/GL/GLPlatform.h"
#include "renderer/GL/windows/GLContextWGL.h"

namespace CodeHero {

GLWindow::GLWindow() {}

GLWindow::~GLWindow() {
    if (m_pWindow) {
        m_pWindow->Destroy();
    }
}

bool GLWindow::Create(uint32_t iWidth, uint32_t iHeight) {
    auto platformModule =
        ModuleManager::Get()->LoadModuleType<PlatformModule>(TEXT("CodeHero.Platform"));
    PlatformWindowParams params;
    params.flags = WindowFlags::WF_POS_DEFAULT;
    params.width = iWidth;
    params.height = iHeight;

    m_pWindow.reset(platformModule->MakeWindow(params));
    if (m_pWindow == nullptr) {
        LOGE << "Failed to create native window. Forcing to terminate.";
        // TODO(pierre) I guess there is more to do here than just that.
        return false;
    }

    m_pContext = std::move(CreateGLContext());

    MakeContextCurrent();

    return true;
}

void GLWindow::MakeContextCurrent() {
    m_pContext->MakeCurrent(m_pWindow);
}

bool GLWindow::ShouldClose() const {
    return false;
}

void GLWindow::SwapBuffers() {
    CodeHero::SwapBuffers(m_pWindow);
}

} // namespace CodeHero