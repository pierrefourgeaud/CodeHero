// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/GLRendererModule.h"

#include "core/logger/Logger.h"
#include "renderer/GL/GLRenderer.h"

namespace CodeHero {

IMPLEMENT_MODULE(GLRendererModule)

Renderer* GLRendererModule::CreateRenderer() {
    return new GLRenderer;
}

} // namespace CodeHero