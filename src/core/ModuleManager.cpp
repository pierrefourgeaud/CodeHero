// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/ModuleManager.h"

#include "core/HAL/SharedLibraryHandler.h"
#include "core/logger/Logger.h"

namespace CodeHero {

typedef Module* (*InitializeModule)(void);

ModuleManager::ModuleManager() = default;
ModuleManager::~ModuleManager() = default;

Module* ModuleManager::LoadModule(const String& iModuleName) {
    auto shLib = SharedLibraryHandler::GetLibraryHandle(iModuleName);

    if (!shLib) {
        LOGF << "Failed to load " << iModuleName;
        return nullptr;
    }

    InitializeModule init = static_cast<InitializeModule>(
        SharedLibraryHandler::GetLibraryExport(shLib, "InitializeModule"));
    if (!init) {
        LOGF << "No entrypoint found for the module " << iModuleName;
        return nullptr;
    }

    return init();
}

} // namespace CodeHero