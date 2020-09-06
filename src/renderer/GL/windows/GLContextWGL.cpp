// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/windows/GLContextWGL.h"

#include "renderer/GL/windows/WGLApi.h"

namespace CodeHero {

GLContextWGL::~GLContextWGL() = default;

bool GLContextWGL::Create() {
    return true;
}

void GLContextWGL::MakeCurrent(const std::unique_ptr<IPlatformWindow>& iWindow) {
    (void)iWindow;
}

} // namespace CodeHero