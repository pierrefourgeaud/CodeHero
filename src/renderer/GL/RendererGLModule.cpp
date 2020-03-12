// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/RendererGLModule.h"

#include "core/logger/Logger.h"
#include "renderer/GL/RendererGL.h"

#include "core/ModuleManager.h"
#include "dummy/DummyModule.h"

namespace CodeHero {

IMPLEMENT_MODULE(RendererGLModule)

Renderer* RendererGLModule::CreateRenderer() {
    auto mod = ModuleManager::Get()->LoadModuleType<DummyModule>(TEXT("CodeHero.Dummy"));
    mod->Dummy();
    LOGI << "CreateRenderer";
    return new RendererGL;
}

} // namespace CodeHero