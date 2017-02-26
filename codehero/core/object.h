// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_OBJECT_H_
#define CODEHERO_CORE_OBJECT_H_

#include <memory>
#include <string>

namespace CodeHero {

// Forward declaration
class EngineContext;

class Object {
public:
    virtual ~Object() {}

    Object(const std::shared_ptr<EngineContext>& iContext) : m_pContext(iContext) {}
    virtual const std::string GetTypeName() = 0;

protected:
    std::shared_ptr<EngineContext> m_pContext;
};

} // namespace CodeHero

#define OBJECT(className) \
    const std::string GetTypeName() { return #className; } \
    static const std::string GetTypeNameStatic() { return #className; }

#define OBJECT_TEMPLATE(className, T) \
    const std::string GetTypeName() { return #className + T::GetTypeNameStatic(); } \
    static const std::string GetTypeNameStatic() { return #className + T::GetTypeNameStatic(); }

#endif // CODEHERO_CORE_OBJECT_H_
