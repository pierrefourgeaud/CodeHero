// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "renderer/Renderer.h"

namespace CodeHero {

class RendererGL : public Renderer {
 public:
    void Draw() override;
};

} // namespace CodeHero