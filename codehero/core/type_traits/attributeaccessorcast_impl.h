// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_CAST_IMPL_H_
#define CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_CAST_IMPL_H_

#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/variant.h"

namespace CodeHero {

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

template <class Class, class Type, class CastTo, class GetFn, class SetFn>
std::shared_ptr<AttributeAccessorImplCast<Class, Type, CastTo, GetFn, SetFn>> MakeAccessorImplCast(GetFn iGet, SetFn iSet) {
    return std::make_shared<AttributeAccessorImplCast<Class, Type, CastTo, GetFn, SetFn>>(iGet, iSet);
}

} // namespace CodeHero

#endif // CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_CAST_IMPL_H_