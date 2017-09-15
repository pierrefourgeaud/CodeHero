// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_OBJECT_DEFINITION_H_
#define CODEHERO_CORE_OBJECT_DEFINITION_H_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "core/variant.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Object;

class AttributeInfo {
public:
    virtual ~AttributeInfo() {}

    virtual bool IsNull() const { return false; }

    void SetType(Variant::Value::Type iType) {
        m_Type = iType;
    }

    Variant::Value::Type GetType() const { return m_Type; }

private:
    Variant::Value::Type m_Type;
};

// This NullAttributeInfo is used to report error on attribute mainly
// TODO(pierre) Maybe changing the API could help not to have to do that ?
class NullAttributeInfo : public AttributeInfo {
public:
    bool IsNull() const override { return true; }
};

using ObjectFactory = std::function<std::shared_ptr<Object>(const std::shared_ptr<EngineContext>&)>;

// TODO(pierre) To reflect on the fact that TypeDefinition might be more appropriate
//              This is not of direct importance
class ObjectDefinition {
public:
    ObjectDefinition(const std::shared_ptr<EngineContext>& iContext);
    ~ObjectDefinition();

    // Those methods are returning an ObjectDefinition& to be chainable
    ObjectDefinition& RegisterFactory(const ObjectFactory& iFactory);
    ObjectDefinition& AddAttribute(const std::string& iName,
                                   Variant::Value::Type iType);

    AttributeInfo& GetAttribute(const std::string& iAttributeName);

    std::shared_ptr<Object> Create() const;

    static AttributeInfo& NullAttribute() {
        static NullAttributeInfo attrib;
        return attrib;
    }

private:
    std::shared_ptr<EngineContext> m_pContext;
    ObjectFactory m_pFactory = nullptr;
    std::unordered_map<std::string, AttributeInfo> m_Attributes;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_OBJECT_DEFINITION_H_
