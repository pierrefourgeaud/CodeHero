// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_IMPL_H_
#define CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_IMPL_H_

#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/variant.h"

namespace CodeHero {

template <class Class, class Type, class GetFn, class SetFn>
class AttributeAccessorImpl : public AttributeAccessor {
public:
    AttributeAccessorImpl(GetFn iGet, SetFn iSet) : m_pGet(iGet), m_pSet(iSet) {}

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
    AttributeAccessorImpl(void*, SetFn iSet) : m_pSet(iSet) {}

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

template <class Class, class Type, class GetFn, class SetFn>
std::shared_ptr<AttributeAccessorImpl<Class, Type, GetFn, SetFn>> MakeAccessorImpl(GetFn iGet,
                                                                                   SetFn iSet) {
    return std::make_shared<AttributeAccessorImpl<Class, Type, GetFn, SetFn>>(iGet, iSet);
}

} // namespace CodeHero

#endif // CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_IMPL_H_