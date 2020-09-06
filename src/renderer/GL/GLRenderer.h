// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "renderer/Renderer.h"

namespace CodeHero {

class GLRenderer : public Renderer {
 public:
    bool Initialize() override;
    bool Cleanup() override;
    void PollEvents() override;
    void Draw() override;

    void SetViewport(uint32_t iX, uint32_t iY, uint32_t iWidth, uint32_t iHeight) override;

    std::shared_ptr<Window> MakeWindow(uint32_t iWidth, uint32_t iHeight) override;
};

} // namespace CodeHero