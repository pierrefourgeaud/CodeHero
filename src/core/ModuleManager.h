// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/CoreAPI.h"
#include "core/String.h"

namespace CodeHero {

// Forward declaration
class Module;
class ModuleManagerImpl;

// TODO(pierre): Make the module manager auto reload the modules that can be
// TODO(pierre): Make a MONOLITHIC version (opposite of multiple ShLib) with statically linked libs
// TODO(pierre): A version "non-monolithic" will exist but without the auto reload too.
// Class that takes care of the different modules that are loaded across the Engine.
class CORE_API ModuleManager {
 public:
    // TODO(pierre): Do we want to make that part of a macro?
    // Disallow COPY and MOVE
    ModuleManager(const ModuleManager&) = delete;
    ModuleManager(ModuleManager&&) = delete;
    ModuleManager& operator=(const ModuleManager&) = delete;
    ModuleManager& operator=(ModuleManager&&) = delete;
    // --

    // Singleton
    static ModuleManager* Get();

    Module* LoadModule(const String& iModuleName);
    // void UnloadModule(const String& iModuleName);

    template <typename ModuleType>
    ModuleType* LoadModuleType(const String& iModuleName) {
        Module* module = LoadModule(iModuleName);
        return reinterpret_cast<ModuleType*>(module);
    }

 private:
    // Singleton
    ModuleManager();
    ~ModuleManager();

    // The fact that we export the library to be used by importers of the library, we cannot simply
    // use STL container/pointers here. We are careful and instanciate this instance in the
    // contructor and delete it in the destructor.
    // TODO(pierre) If planning to have our own UniquePtr implementation, replace with that then.
    ModuleManagerImpl* m_pImpl;
};

} // namespace CodeHero