// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "renderer/IRendererModule.h"

namespace CodeHero {

// Forward declaration
class Renderer;

class GLRendererModule : public IRendererModule {
 public:
    virtual Renderer* CreateRenderer() override;
};

} // namespace CodeHero