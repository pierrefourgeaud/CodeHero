// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

#include "engine/EngineAPI.h"

namespace CodeHero {

// Forward declaration
// class WConsoleLogger;
class Renderer;
class Window;

// EngineLoop export all functions one by one because std::* containers/pointers cannot be exported
// easily. I was too lazy to create a EngineLoopImpl that would take care of that in the source
// file. Maybe one day I will be less lazy...
class EngineLoop final {
 public:
    ENGINE_API EngineLoop();
    ENGINE_API ~EngineLoop();

    bool ENGINE_API PreInit();
    bool ENGINE_API Init();
    void ENGINE_API Tick();
    void ENGINE_API Cleanup();

    bool ENGINE_API ExitEngineRequested() const;

 private:
    //  std::unique_ptr<WConsoleLogger> m_pConsoleLogger;
    std::unique_ptr<Renderer> m_pRenderer;
    std::shared_ptr<Window> m_pWindow;
};

} // namespace CodeHero