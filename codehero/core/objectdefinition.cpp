// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/objectdefinition.h"

namespace CodeHero {

ObjectDefinition::ObjectDefinition(const std::shared_ptr<EngineContext>& iContext, const std::string& iName)
    : m_pContext(iContext)
    , m_Name(iName) {}

ObjectDefinition::~ObjectDefinition() {}

ObjectDefinition& ObjectDefinition::RegisterFactory(const ObjectFactory& iFactory) {
    m_pFactory = iFactory;
    return *this;
}

ObjectDefinition& ObjectDefinition::AddAttribute(const std::string& iName,
                                                 Variant::Value::Type iType,
                                                 const std::shared_ptr<AttributeAccessor>& iAccessor) {
    AttributeInfo attrib;
    attrib.SetType(iType);
    attrib.SetAccessor(iAccessor);

    m_Attributes[iName] = attrib;

    return *this;
}

AttributeInfo& ObjectDefinition::GetAttribute(const std::string& iAttributeName) {
    auto attrib = m_Attributes.find(iAttributeName);
    if (attrib == m_Attributes.end()) {
        return ObjectDefinition::NullAttribute();
    }

    return attrib->second;
}

std::shared_ptr<Object> ObjectDefinition::Create() const {
    if (m_pFactory == nullptr) {
        return nullptr;
    }

    return m_pFactory(m_pContext);
}

} // namespace CodeHero