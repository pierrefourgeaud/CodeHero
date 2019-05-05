// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/serializable.h"

namespace CodeHero {

std::unordered_map<std::string, Builder> Serializable::m_Builders;

Serializable::Serializable(const std::shared_ptr<EngineContext>& iContext) : Object(iContext) {}

Serializable::~Serializable() {}

} // namespace CodeHero