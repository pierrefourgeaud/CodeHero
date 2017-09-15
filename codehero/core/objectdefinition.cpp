// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/objectdefinition.h"

namespace CodeHero {

ObjectDefinition::ObjectDefinition(const std::shared_ptr<EngineContext>& iContext)
    : m_pContext(iContext) {}

ObjectDefinition::~ObjectDefinition() {}

ObjectDefinition& ObjectDefinition::RegisterFactory(const ObjectFactory& iFactory) {
    m_pFactory = iFactory;
    return *this;
}

ObjectDefinition& ObjectDefinition::AddAttribute(const std::string& iName,
                                                 Variant::Value::Type iType) {
    AttributeInfo attrib;
    attrib.SetType(iType);

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