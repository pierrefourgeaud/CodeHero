// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/ModuleManager.h"

#include <unordered_map>

#include "core/HAL/SharedLibraryHandler.h"
#include "core/logger/Logger.h"

#include <iostream>

namespace CodeHero {

typedef Module* (*InitializeModule)(void);

class ModuleManagerImpl {
 public:
    Module* LoadModule(const String& iModuleName) {
        auto mod = m_LoadedModules.find(iModuleName);
        if (mod != m_LoadedModules.end()) {
            return mod->second->module;
        }

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

        auto newModule = init();
        auto info = std::make_unique<ModuleInfo>();
        info->handle = shLib;
        info->module = newModule;
        m_LoadedModules[iModuleName] = std::move(info);

        return newModule;
    }

 private:
    struct ModuleInfo {
        void* handle;
        Module* module;
    };

    std::unordered_map<String, std::unique_ptr<ModuleInfo>> m_LoadedModules;
};

// static
ModuleManager* ModuleManager::Get() {
    static ModuleManager mgr;
    return &mgr;
}

ModuleManager::ModuleManager() {
    m_pImpl = new ModuleManagerImpl;
}
ModuleManager::~ModuleManager() {
    delete m_pImpl;
};

Module* ModuleManager::LoadModule(const String& iModuleName) {
    return m_pImpl->LoadModule(iModuleName);
}

} // namespace CodeHero