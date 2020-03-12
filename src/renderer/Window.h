// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/TypeDefs.h"

namespace CodeHero {

class Window {
 public:
    virtual ~Window() {}
    virtual bool Create(uint32_t iWidth, uint32_t iHeight) = 0;
    virtual void MakeContextCurrent() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void SwapBuffers() = 0;
};

} // namespace CodeHero