// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "engine/EngineLoop.h"

#include "core/Core.h"
#include "core/ModuleManager.h"
#include "core/logger/Logger.h"
#include "renderer/Renderer.h"
#include "renderer/RendererModule.h"
#include "renderer/Window.h"

namespace CodeHero {

EngineLoop::EngineLoop() = default;
EngineLoop::~EngineLoop() = default;

bool EngineLoop::PreInit() {
    CoreInitialize();

    return true;
}

bool EngineLoop::Init() {
    auto rendererModule =
        ModuleManager::Get()->LoadModuleType<RendererModule>(TEXT("CodeHero.Renderer.OpenGL"));
    if (!rendererModule) {
        return false;
    }

    m_pRenderer.reset(rendererModule->CreateRenderer());
    if (!m_pRenderer->Initialize()) {
        LOGE << "Failed to initialize renderer.";
        return false;
    }

    m_pWindow = m_pRenderer->CreateWindow(800, 600);

    return true;
}

void EngineLoop::Tick() {
    m_pWindow->SwapBuffers();
    m_pRenderer->PollEvents();
}

void EngineLoop::Cleanup() {
    if (m_pWindow) {
        m_pWindow.reset();
    }

    if (m_pRenderer) {
        m_pRenderer->Cleanup();
        m_pRenderer.reset();
    }

    // At the very end
    CoreTearDown();
}

bool EngineLoop::ExitEngineRequested() const {
    return !m_pWindow || m_pWindow->ShouldClose();
}

} // namespace CodeHero