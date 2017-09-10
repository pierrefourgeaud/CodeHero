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

/**
 * class TypeInfo
 * Very simple reflection mechanism to help with going through the inheritance tree.
 * As much as I tried to keep the inheritance tree small, there are sometimes needs
 * for inheritance.
 * The TypeInfo is used mainly in case of serialization of an object, therefor enabling:
 *   - Save/Load object description from files
 *   - Serialization for network usage
 *   - Usage in scripting
*/
class TypeInfo {
public:
    TypeInfo(const std::string& iTypeName, const std::shared_ptr<TypeInfo>& iBaseTypeInfo)
        : m_TypeName(iTypeName)
        , m_BaseTypeInfo(iBaseTypeInfo) {}

    const std::string& GetTypeName() const { return m_TypeName; }
    const std::shared_ptr<TypeInfo>& GetBaseTypeInfo() const { return m_BaseTypeInfo; }

private:
    const std::string m_TypeName;
    const std::shared_ptr<TypeInfo> m_BaseTypeInfo;
};

class Object {
public:
    virtual ~Object() {}

    Object(const std::shared_ptr<EngineContext>& iContext) : m_pContext(iContext) {}
    virtual const std::string GetTypeName() = 0;

    static const std::shared_ptr<TypeInfo>& GetTypeInfoStatic() {
        static const std::shared_ptr<TypeInfo> nullType = nullptr;
        return nullType;
    }

protected:
    std::shared_ptr<EngineContext> m_pContext;
};

} // namespace CodeHero

#define OBJECT(className, baseClassName) \
    const std::string GetTypeName() override { return GetTypeInfoStatic()->GetTypeName(); } \
    static const std::string& GetTypeNameStatic() { return GetTypeInfoStatic()->GetTypeName(); } \
    static const std::shared_ptr<TypeInfo>& GetTypeInfoStatic() { \
        static const auto typeInfoStatic = std::make_shared<TypeInfo>(#className, baseClassName::GetTypeInfoStatic()); \
        return typeInfoStatic; \
    } \

#define OBJECT_TEMPLATE(className, T, baseClassName) \
    const std::string GetTypeName() override { return GetTypeInfoStatic()->GetTypeName(); } \
    static const std::string& GetTypeNameStatic() { return GetTypeInfoStatic()->GetTypeName(); } \
    static const std::shared_ptr<TypeInfo>& GetTypeInfoStatic() { \
        static const auto typeInfoStatic = std::make_shared<TypeInfo>(#className + T::GetTypeNameStatic(), baseClassName::GetTypeInfoStatic()); \
        return typeInfoStatic; \
    } \

#endif // CODEHERO_CORE_OBJECT_H_
