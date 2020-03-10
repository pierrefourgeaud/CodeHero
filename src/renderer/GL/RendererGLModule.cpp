// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/RendererGLModule.h"

#include "core/logger/Logger.h"
#include "core/logger/WConsoleLogger.h"
#include "renderer/GL/RendererGL.h"

namespace CodeHero {

IMPLEMENT_MODULE(RendererGLModule)

Renderer* RendererGLModule::CreateRenderer() {
    LOGI << "CreateRenderer";
    return new RendererGL;
}

} // namespace CodeHero