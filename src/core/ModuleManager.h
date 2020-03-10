// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/TypeDefs.h"

namespace CodeHero {

// Forward declaration
class Module;

// TODO(pierre): Make the module manager auto reload the modules that can be
// TODO(pierre): Make a MONOLITHIC version (opposite of multiple ShLib) with statically linked libs
// TODO(pierre): A version "non-monolithic" will exist but without the auto reload too.
// Class that takes care of the different modules that are loaded across the Engine.
class ModuleManager {
 public:
    // TODO(pierre): Do we want to make that part of a macro?
    // Disallow COPY and MOVE
    ModuleManager(const ModuleManager&) = delete;
    ModuleManager(ModuleManager&&) = delete;
    ModuleManager& operator=(const ModuleManager&) = delete;
    ModuleManager& operator=(ModuleManager&&) = delete;
    // --

    ModuleManager();
    ~ModuleManager();

    Module* LoadModule(const String& iModuleName);
    // void UnloadModule(const String& iModuleName);

    template <typename ModuleType>
    ModuleType* LoadModuleType(const String& iModuleName) {
        Module* module = LoadModule(iModuleName);
        return reinterpret_cast<ModuleType*>(module);
    }

 private:
};

} // namespace CodeHero