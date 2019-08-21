// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_ENGINECONTEXT_H_
#define CODEHERO_CORE_ENGINECONTEXT_H_

#include <memory>
#include <string>
#include <unordered_map>

namespace CodeHero {

// Forward declaration
class System;

class EngineContext {
public:
    void RegisterSubsystem(System* iSystem);

    template <class T>
    T* GetSubsystem() {
        return static_cast<T*>(GetSubsystem(T::GetTypeNameStatic()));
    }

    System* GetSubsystem(const std::string& iSystemName);

private:
    std::unordered_map<std::string, std::unique_ptr<System>> m_SubSystems;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_ENGINECONTEXT_H_
