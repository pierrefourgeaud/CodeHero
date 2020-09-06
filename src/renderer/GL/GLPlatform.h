// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

namespace CodeHero {

// Forward declarations
class IGLContext;
class IPlatformWindow;

bool GLInit();
void GLTerminate();
std::unique_ptr<IGLContext> CreateGLContext();
bool SwapBuffers(const std::unique_ptr<IPlatformWindow>& iWindow);

} // namespace CodeHero