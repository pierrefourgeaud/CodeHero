// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPE_TRAITS_OBJECT_DEFINITION_H_
#define CODEHERO_CORE_TYPE_TRAITS_OBJECT_DEFINITION_H_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "core/assert.h"
#include "core/type_traits/attributeinfo.h"
#include "core/variant.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Object;
class TypeInfo;

using ObjectFactory = std::function<std::shared_ptr<Object>(const std::shared_ptr<EngineContext>&)>;

// TODO(pierre) To reflect on the fact that TypeDefinition might be more appropriate
//              This is not of direct importance
class ObjectDefinition {
public:
    ObjectDefinition(const std::shared_ptr<EngineContext>& iContext, const std::string& iName);
    ~ObjectDefinition();

    // Those methods are returning an ObjectDefinition& to be chainable
    ObjectDefinition& RegisterFactory(const ObjectFactory& iFactory);
    ObjectDefinition& RegisterTypeInfo(const std::shared_ptr<TypeInfo>& iTypeInfo);
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
    std::shared_ptr<TypeInfo> m_pTypeInfo;
    std::unordered_map<std::string, AttributeInfo> m_Attributes;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_TYPE_TRAITS_OBJECT_DEFINITION_H_
