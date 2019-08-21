// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_OBJECT_H_
#define CODEHERO_CORE_OBJECT_H_

#include <memory>
#include <string>
#include <unordered_map>

namespace CodeHero {

// Forward declaration
class EngineContext;
class ObjectDefinition;

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
        : m_TypeName(iTypeName), m_BaseTypeInfo(iBaseTypeInfo) {}

    const std::string& GetTypeName() const { return m_TypeName; }
    const std::shared_ptr<TypeInfo>& GetBaseTypeInfo() const { return m_BaseTypeInfo; }

    bool IsA(const std::shared_ptr<TypeInfo>& iOther) const;

private:
    const std::string m_TypeName;
    const std::shared_ptr<TypeInfo> m_BaseTypeInfo;
};

class Object {
public:
    virtual ~Object() {}

    Object(const std::shared_ptr<EngineContext>& iContext);

    bool IsInstanceOf(const std::shared_ptr<TypeInfo>& iType) const;

    virtual const std::string GetTypeName() const = 0;
    virtual const std::shared_ptr<TypeInfo>& GetTypeInfo() const { return GetTypeInfoStatic(); }

    static const std::shared_ptr<TypeInfo>& GetTypeInfoStatic() {
        static const std::shared_ptr<TypeInfo> nullType = nullptr;
        return nullType;
    }

    static std::shared_ptr<ObjectDefinition> CreateDefinition(
        const std::shared_ptr<EngineContext>& iContext,
        const std::string& iName);
    static std::shared_ptr<ObjectDefinition> GetDefinition(const std::string& iName);

protected:
    std::shared_ptr<EngineContext> m_pContext;

    static std::unordered_map<std::string, std::shared_ptr<ObjectDefinition>> m_Definitions;
};

} // namespace CodeHero

#define OBJECT(className, baseClassName)                                                          \
    const std::string GetTypeName() const override { return GetTypeInfoStatic()->GetTypeName(); } \
    const std::shared_ptr<TypeInfo>& GetTypeInfo() const override { return GetTypeInfoStatic(); } \
    static const std::string& GetTypeNameStatic() { return GetTypeInfoStatic()->GetTypeName(); }  \
    static const std::shared_ptr<TypeInfo>& GetTypeInfoStatic() {                                 \
        static const auto typeInfoStatic =                                                        \
            std::make_shared<TypeInfo>(#className, baseClassName::GetTypeInfoStatic());           \
        return typeInfoStatic;                                                                    \
    }

#define OBJECT_TEMPLATE(className, T, baseClassName)                                              \
    const std::string GetTypeName() const override { return GetTypeInfoStatic()->GetTypeName(); } \
    const std::shared_ptr<TypeInfo>& GetTypeInfo() const override { return GetTypeInfoStatic(); } \
    static const std::string& GetTypeNameStatic() { return GetTypeInfoStatic()->GetTypeName(); }  \
    static const std::shared_ptr<TypeInfo>& GetTypeInfoStatic() {                                 \
        static const auto typeInfoStatic = std::make_shared<TypeInfo>(                            \
            #className + T::GetTypeNameStatic(), baseClassName::GetTypeInfoStatic());             \
        return typeInfoStatic;                                                                    \
    }

// Needs to be called for object that contains static ::Create(const shared_ptr<EngineContext>&);
#define CH_REGISTER_OBJECT(Class)                                \
    auto objectDef = Object::CreateDefinition(iContext, #Class); \
    objectDef->RegisterFactory(Class::Create);                   \
    objectDef->RegisterTypeInfo(Class::GetTypeInfoStatic());

// Needs to be called only after a CH_REGISTER_OBJECT (the objectDef is used here)
#define CH_OBJECT_ATTRIBUTE(Class, Name, Type, VariantType, GetFunction, SetFunction) \
    objectDef->AddAttribute(Name, VariantType,                                        \
                            MakeAccessorImpl<Class, Type>(GetFunction, SetFunction));

// Needs to be called only after a CH_REGISTER_OBJECT (the objectDef is used here)
#define CH_OBJECT_ATTRIBUTE_CAST(Class, Name, Type, CastTo, VariantType, GetFunction, SetFunction) \
    objectDef->AddAttribute(Name, VariantType,                                                     \
                            MakeAccessorCastImpl<Class, Type, CastTo>(GetFunction, SetFunction));

// Needs to be called only after a CH_REGISTER_OBJECT (the objectDef is used here)
#define CH_OBJECT_ATTRIBUTE_CUSTOM(Class, Name, Type, VariantType, GetFunction, SetFunction) \
    objectDef->AddAttribute(Name, VariantType,                                               \
                            MakeAccessorCustomImpl<Class, Type>(GetFunction, SetFunction));

// Needs to be called only after a CH_REGISTER_OBJECT (the objectDef is used here)
#define CH_OBJECT_ATTRIBUTE_ENUM(Class, Name, Type, GetFunction, SetFunction, FromStringFunction, \
                                 ToStringFunction)                                                \
    objectDef->AddAttribute(Name, Variant::Value::VVT_String,                                     \
                            MakeAccessorEnumImpl<Class, Type>(                                    \
                                GetFunction, SetFunction, FromStringFunction, ToStringFunction));

#endif // CODEHERO_CORE_OBJECT_H_
