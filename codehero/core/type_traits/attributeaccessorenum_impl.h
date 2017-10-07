// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_ENUM_IMPL_H_
#define CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_ENUM_IMPL_H_

#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/variant.h"

namespace CodeHero {

template <class Class, class Type, class GetFn, class SetFn>
class AttributeAccessorEnumImpl : public AttributeAccessor {
public:
    using FromStringFn = std::function<Type(const std::string&)>;
    using ToStringFn = std::function<std::string(Type)>;

    AttributeAccessorEnumImpl(GetFn iGet, SetFn iSet, FromStringFn iFromString, ToStringFn iToString)
        : m_pGet(iGet)
        , m_pSet(iSet)
        , m_pFromString(iFromString)
        , m_pToString(iToString) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        const Class* classPtr = static_cast<const Class*>(iPtr);
        return Variant(m_pToString((classPtr->*m_pGet)()));
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(m_pFromString(iValue.GetString()));
    }

private:
    GetFn m_pGet;
    SetFn m_pSet;
    FromStringFn m_pFromString;
    ToStringFn m_pToString;
};

template <class Class, class Type, class SetFn>
class AttributeAccessorEnumImpl<Class, Type, std::nullptr_t, SetFn> : public AttributeAccessor {
public:
    using FromStringFn = std::function<Type(const std::string&)>;

    AttributeAccessorEnumImpl(void*, SetFn iSet, const FromStringFn& iFromString, void*)
        : m_pSet(iSet)
        , m_pFromString(iFromString) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        return Variant();
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(m_pFromString(iValue.Get<Type>()));
    }

private:
    SetFn m_pSet;
    FromStringFn m_pFromString;
};

template <class Class, class Type, class GetFn, class SetFn>
std::shared_ptr<AttributeAccessorEnumImpl<Class, Type, GetFn, SetFn>>
    MakeAccessorEnumImpl(GetFn iGet,
                         SetFn iSet,
                         const std::function<Type(const std::string&)>& iFromString,
                         const std::function<std::string(Type)> iToString) {
    return std::make_shared<AttributeAccessorEnumImpl<Class, Type, GetFn, SetFn>>(iGet, iSet, iFromString, iToString);
}

} // namespace CodeHero

#endif // CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_ENUM_IMPL_H_