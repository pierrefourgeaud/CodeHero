// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"
#include "core/logger/Logger.h"

namespace CodeHero {

class Module {
 public:
};

#define IMPLEMENT_MODULE(ModuleClass)                        \
    DECLARE_LOG_MODULE(ModuleClass)                          \
    extern "C" SHLIBEXPORT ModuleClass* InitializeModule() { \
        DEFINE_LOG_MODULE(ModuleClass)                       \
        return new ModuleClass();                            \
    }

} // namespace CodeHero