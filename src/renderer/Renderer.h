// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

#include "core/HAL/Platform.h"

namespace CodeHero {

// Forward declaration
class Window;

class Renderer {
 public:
    virtual bool Initialize() = 0;
    virtual bool Cleanup() = 0;
    virtual void PollEvents() = 0;
    virtual void Draw() = 0;

    // Factory methods
#if defined(PLATFORM_WINDOWS)
#if defined(CreateWindow)
#undef CreateWindow
#endif
#endif
    virtual std::shared_ptr<Window> CreateWindow(uint32_t iWidth, uint32_t iHeight) = 0;
};

} // namespace CodeHero