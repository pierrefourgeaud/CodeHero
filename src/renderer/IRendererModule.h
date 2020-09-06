// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/IModule.h"

namespace CodeHero {

// Forward declaration
class Renderer;

class IRendererModule : public IModule {
 public:
    virtual Renderer* CreateRenderer() = 0;
};

} // namespace CodeHero