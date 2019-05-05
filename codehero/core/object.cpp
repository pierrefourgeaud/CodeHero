// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/object.h"
#include "core/type_traits/objectdefinition.h"

namespace CodeHero {

/**
 * TypeInfo
 */
bool TypeInfo::IsA(const std::shared_ptr<TypeInfo>& iOther) const {
    bool res = this == iOther.get();

    // If the two types are not equal, let's look at the parent
    if (!res) {
        auto parent = this->GetBaseTypeInfo();
        res = parent ? parent->IsA(iOther) : false;
    }

    return res;
}

/**
 * Object
 */
std::unordered_map<std::string, std::shared_ptr<ObjectDefinition>> Object::m_Definitions;

Object::Object(const std::shared_ptr<EngineContext>& iContext) : m_pContext(iContext) {}

bool Object::IsInstanceOf(const std::shared_ptr<TypeInfo>& iType) const {
    return GetTypeInfo()->IsA(iType);
}

// static
std::shared_ptr<ObjectDefinition> Object::CreateDefinition(
    const std::shared_ptr<EngineContext>& iContext,
    const std::string& iName) {
    auto def = std::make_shared<ObjectDefinition>(iContext, iName);
    m_Definitions[iName] = def;
    return def;
}

std::shared_ptr<ObjectDefinition> Object::GetDefinition(const std::string& iName) {
    auto obj = m_Definitions.find(iName);
    if (obj == m_Definitions.end()) {
        return nullptr;
    }

    return obj->second;
}

} // namespace CodeHero