// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_OBJECT_DEFINITION_H_
#define CODEHERO_CORE_OBJECT_DEFINITION_H_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "core/assert.h"
#include "core/variant.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Object;
class Serializable;

class AttributeAccessor {
public:
    virtual ~AttributeAccessor() {}

    virtual Variant Get(const Serializable* iPtr) const = 0;
    virtual void Set(Serializable* iPtr, const Variant& iValue) = 0;
};

template <class Class, class Type, class GetFn, class SetFn>
class AttributeAccessorImpl : public AttributeAccessor {
public:
    AttributeAccessorImpl(GetFn iGet, SetFn iSet)
        : m_pGet(iGet)
        , m_pSet(iSet) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        const Class* classPtr = static_cast<const Class*>(iPtr);
        return Variant((classPtr->*m_pGet)());
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(iValue.Get<Type>());
    }

private:
    GetFn m_pGet;
    SetFn m_pSet;
};

/*
 * Specialization of the Attribute Accessor that doesn't provide a Getter.
 * This is used for SetMethods only when Getting the attribute is not possible
 */
template <class Class, class Type, class SetFn>
class AttributeAccessorImpl<Class, Type, std::nullptr_t, SetFn> : public AttributeAccessor {
public:
    AttributeAccessorImpl(void*, SetFn iSet)
        : m_pSet(iSet) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        return Variant();
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(iValue.Get<Type>());
    }

private:
    SetFn m_pSet;
};

// This is a special class. This requires that:
//   - Type can be casted into CastTo (Usually instance of CastTo that is a child of Type)
//   - Also requires that CastTo can be cast statically to Type (again inheritance usually)
// TODO(pierre) This is error prone - We should try to find a better way to achieve this
template <class Class, class Type, class CastTo, class GetFn, class SetFn>
class AttributeAccessorImplCast : public AttributeAccessor {
public:
    AttributeAccessorImplCast(GetFn iGet, SetFn iSet)
        : m_pGet(iGet)
        , m_pSet(iSet) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        const Class* classPtr = static_cast<const Class*>(iPtr);
        return Variant((classPtr->*m_pGet)());
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        // TODO(pierre) It would be nice to make it safe
        //   One way would be to use the information that we have on our type
        //   i.e: "Shader" IsTypeOf "Serializable"
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(std::static_pointer_cast<CastTo>(iValue.Get<Type>()));
    }

private:
    GetFn m_pGet;
    SetFn m_pSet;
};

template <class Class, class Type, class CastTo, class SetFn>
class AttributeAccessorImplCast<Class, Type, CastTo, std::nullptr_t, SetFn> : public AttributeAccessor {
public:
    AttributeAccessorImplCast(void*, SetFn iSet)
        : m_pSet(iSet) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        return Variant();
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        // TODO(pierre) It would be nice to make it safe
        //   One way would be to use the information that we have on our type
        //   i.e: "Shader" IsTypeOf "Serializable"
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(std::static_pointer_cast<CastTo>(iValue.Get<Type>()));
    }

private:
    SetFn m_pSet;
};

template <class Class, class Type, class GetFn, class SetFn>
std::shared_ptr<AttributeAccessorImpl<Class, Type, GetFn, SetFn>> MakeAccessorImpl(GetFn iGet, SetFn iSet) {
    return std::make_shared<AttributeAccessorImpl<Class, Type, GetFn, SetFn>>(iGet, iSet);
}

template <class Class, class Type, class CastTo, class GetFn, class SetFn>
std::shared_ptr<AttributeAccessorImplCast<Class, Type, CastTo, GetFn, SetFn>> MakeAccessorImplCast(GetFn iGet, SetFn iSet) {
    return std::make_shared<AttributeAccessorImplCast<Class, Type, CastTo, GetFn, SetFn>>(iGet, iSet);
}

class AttributeInfo {
public:
    explicit AttributeInfo(bool iIsNullAttribute = false)
        : m_IsNullAttribute(iIsNullAttribute) {}
    ~AttributeInfo() {}

    bool IsNull() const { return m_IsNullAttribute; }

    void SetType(Variant::Value::Type iType) {
        m_Type = iType;
    }

    void SetName(const std::string& iName) {
        m_Name = iName;
    }

    void SetAccessor(const std::shared_ptr<AttributeAccessor>& iAccessor) {
        m_pAccessor = iAccessor;
    }

    Variant::Value::Type GetType() const { return m_Type; }
    const std::string& GetName() const { return m_Name; }
    const std::shared_ptr<AttributeAccessor>& GetAccessor() const { return m_pAccessor; }

private:
    bool m_IsNullAttribute;
    Variant::Value::Type m_Type;
    std::string m_Name;
    std::shared_ptr<AttributeAccessor> m_pAccessor;
};

using ObjectFactory = std::function<std::shared_ptr<Object>(const std::shared_ptr<EngineContext>&)>;

// TODO(pierre) To reflect on the fact that TypeDefinition might be more appropriate
//              This is not of direct importance
class ObjectDefinition {
public:
    ObjectDefinition(const std::shared_ptr<EngineContext>& iContext, const std::string& iName);
    ~ObjectDefinition();

    // Those methods are returning an ObjectDefinition& to be chainable
    ObjectDefinition& RegisterFactory(const ObjectFactory& iFactory);
    ObjectDefinition& AddAttribute(const std::string& iName,
                                   Variant::Value::Type iType,
                                   const std::shared_ptr<AttributeAccessor>& iAccessor);

    AttributeInfo& GetAttribute(const std::string& iAttributeName);

    const std::string& GetName() const { return m_Name; }

    std::shared_ptr<Object> Create() const;

    static AttributeInfo& NullAttribute() {
        static AttributeInfo attrib(true);
        return attrib;
    }

private:
    std::shared_ptr<EngineContext> m_pContext;
    std::string m_Name;
    ObjectFactory m_pFactory = nullptr;
    std::unordered_map<std::string, AttributeInfo> m_Attributes;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_OBJECT_DEFINITION_H_
