// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"

namespace CodeHero {

class Renderer {
 public:
    virtual void Draw() = 0;
};

} // namespace CodeHero