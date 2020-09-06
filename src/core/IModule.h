// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"

namespace CodeHero {

class IModule {
 public:
};

#define IMPLEMENT_MODULE(ModuleClass) \
    extern "C" SHLIBEXPORT ModuleClass* InitializeModule() { return new ModuleClass(); }

} // namespace CodeHero