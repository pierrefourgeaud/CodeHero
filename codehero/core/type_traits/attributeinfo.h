// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_INFO_H_
#define CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_INFO_H_

#include "core/variant.h"

namespace CodeHero {

// Forward declaration
class AttributeAccessor;

class AttributeInfo {
   public:
    explicit AttributeInfo(bool iIsNullAttribute = false) : m_IsNullAttribute(iIsNullAttribute) {}
    ~AttributeInfo() {}

    bool IsNull() const { return m_IsNullAttribute; }

    void SetType(Variant::Value::Type iType) { m_Type = iType; }

    void SetName(const std::string& iName) { m_Name = iName; }

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

} // namespace CodeHero

#endif // CODEHERO_CORE_TYPE_TRAITS_ATTRIBUTE_INFO_H_