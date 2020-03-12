// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "renderer/Renderer.h"

namespace CodeHero {

class RendererGL : public Renderer {
 public:
    bool Initialize() override;
    bool Cleanup() override;
    void PollEvents() override;
    void Draw() override;

    std::shared_ptr<Window> CreateWindow(uint32_t iWidth, uint32_t iHeight) override;
};

} // namespace CodeHero