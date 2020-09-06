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

    // TODO(pierre) We most likely want to create a wrapper object for the Viewport so it can
    // be used in other places than the renderer if required.
    virtual void SetViewport(uint32_t iX, uint32_t iY, uint32_t iWidth, uint32_t iHeight) = 0;

    // Factory methods
    // NOTE: Factory method in CodeHero are written with Create* style. This is
    // the only exception throughout the code because Windows headers define
    // a CreateWindow macro that conflict with this. There are methods to cope
    // with this but I don't have the time nor the will to deal with that so
    // MakeWindow it is.
    virtual std::shared_ptr<Window> MakeWindow(uint32_t iWidth, uint32_t iHeight) = 0;
};

} // namespace CodeHero