// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_LOGGING_ILOGLISTENER_H_
#define CODEHERO_CORE_LOGGING_ILOGLISTENER_H_

#include <string>

namespace CodeHero {

// Forward declarations.
enum class ELogLevel;

class ILogListener {
public:
    virtual ~ILogListener() {}
    virtual void Notify(const std::string& iLog, ELogLevel iLevel) = 0;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_LOGGING_ILOGLISTENER_H_
