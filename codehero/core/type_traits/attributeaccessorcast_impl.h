// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_CAST_IMPL_H_
#define CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_CAST_IMPL_H_

#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/variant.h"

// TODO(pierre) It seems that the GetTypeInfoStatic call will require including everyone of the
// header declaring the type use there.
// We should find a way to avoid this !!
#include "graphics/mesh.h"

namespace CodeHero {

// This is a special class. This requires that:
//   - Type can be casted into CastTo (Usually instance of CastTo that is a child of Type)
//   - Also requires that CastTo can be cast statically to Type (again inheritance usually)
// TODO(pierre) This is error prone - We should try to find a better way to achieve this
template <class Class, class Type, class CastTo, class GetFn, class SetFn>
class AttributeAccessorCastImpl : public AttributeAccessor {
public:
    AttributeAccessorCastImpl(GetFn iGet, SetFn iSet) : m_pGet(iGet), m_pSet(iSet) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        const Class* classPtr = static_cast<const Class*>(iPtr);
        return Variant((classPtr->*m_pGet)());
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        CH_ASSERT(iValue.Get<Type>()->IsInstanceOf(CastTo::GetTypeInfoStatic()));
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(std::static_pointer_cast<CastTo>(iValue.Get<Type>()));
    }

private:
    GetFn m_pGet;
    SetFn m_pSet;
};

template <class Class, class Type, class CastTo, class SetFn>
class AttributeAccessorCastImpl<Class, Type, CastTo, std::nullptr_t, SetFn>
    : public AttributeAccessor {
public:
    AttributeAccessorCastImpl(void*, SetFn iSet) : m_pSet(iSet) {}

    Variant Get(const Serializable* iPtr) const override {
        CH_ASSERT(iPtr);
        return Variant();
    }

    void Set(Serializable* iPtr, const Variant& iValue) override {
        CH_ASSERT(iPtr);
        CH_ASSERT(iValue.Get<Type>()->IsInstanceOf(CastTo::GetTypeInfoStatic()));
        Class* classPtr = static_cast<Class*>(iPtr);
        (classPtr->*m_pSet)(std::static_pointer_cast<CastTo>(iValue.Get<Type>()));
    }

private:
    SetFn m_pSet;
};

template <class Class, class Type, class CastTo, class GetFn, class SetFn>
std::shared_ptr<AttributeAccessorCastImpl<Class, Type, CastTo, GetFn, SetFn>> MakeAccessorCastImpl(
    GetFn iGet,
    SetFn iSet) {
    return std::make_shared<AttributeAccessorCastImpl<Class, Type, CastTo, GetFn, SetFn>>(iGet,
                                                                                          iSet);
}

} // namespace CodeHero

#endif // CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_CAST_IMPL_H_