// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_SERIALIZABLE_H_
#define CODEHERO_CORE_SERIALIZABLE_H_

#include <functional>
#include <string>
#include <unordered_map>
#include "core/object.h"
#include "core/variant.h"

namespace CodeHero {

// Forward declaration
class Serializable;

using Builder = std::function<std::shared_ptr<Serializable>(const std::shared_ptr<EngineContext>&)>;

class Attribute {
    Variant m_Value;
};

class Serializable : public Object {
public:
    OBJECT(Serializable, Object)

    Serializable(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Serializable();

    static void RegisterSerializable(const std::string& iName, const Builder& iBuilder);

private:
    static std::unordered_map<std::string, Builder> m_Builders;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_SERIALIZABLE_H_
