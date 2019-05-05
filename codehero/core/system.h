// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_SYSTEM_H_
#define CODEHERO_CORE_SYSTEM_H_

#include "core/errors.h"
#include "core/object.h"

namespace CodeHero {

class System : public Object {
   public:
    OBJECT(System, Object);

    System(const std::shared_ptr<EngineContext>& iContext) : Object(iContext) {}
    virtual ~System() {}

    virtual Error Initialize() = 0;
    virtual Error Cleanup() = 0;

   private:
};

} // namespace CodeHero

#endif // CODEHERO_CORE_SYSTEM_H_
