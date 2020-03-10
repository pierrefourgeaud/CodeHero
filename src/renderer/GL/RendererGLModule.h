// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"

#include "renderer/RendererModule.h"

namespace CodeHero {

// Forward declaration
class Renderer;

class RendererGLModule : public RendererModule {
 public:
    virtual Renderer* CreateRenderer() override;
};

} // namespace CodeHero