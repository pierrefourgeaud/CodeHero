// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "renderer/GL/IGLContext.h"

// TODO(pierre) We might to implement a PIMPL to avoid including
// this header here.
#include <windows.h>

namespace CodeHero {

class GLContextWGL : public IGLContext {
 public:
    ~GLContextWGL() override;

    bool Create() override;
    void MakeCurrent(const std::unique_ptr<IPlatformWindow>& iWindow) override;

 private:
    HGLRC m_Context;
};

} // namespace CodeHero