// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_H_
#define CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_H_

namespace CodeHero {

// Forward declaration
class Serializable;
class Variant;

class AttributeAccessor {
   public:
    virtual ~AttributeAccessor() {}

    virtual Variant Get(const Serializable* iPtr) const = 0;
    virtual void Set(Serializable* iPtr, const Variant& iValue) = 0;
};

} // namespace CodeHero

#include "core/type_traits/attributeaccessor_impl.h"
#include "core/type_traits/attributeaccessorcast_impl.h"
#include "core/type_traits/attributeaccessorcustom_impl.h"
#include "core/type_traits/attributeaccessorenum_impl.h"

#endif // CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_ACCESSOR_H_