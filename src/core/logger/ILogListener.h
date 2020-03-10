// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/TypeDefs.h"

namespace CodeHero {

// Forward declarations.
enum class ELogLevel;

class ILogListener {
 public:
    virtual ~ILogListener() {}
    virtual void Notify(const String& iLog, ELogLevel iLevel) = 0;
};

} // namespace CodeHero