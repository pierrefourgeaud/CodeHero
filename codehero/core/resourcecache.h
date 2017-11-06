// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RESOURCECACHE_H
#define CODEHERO_CORE_RESOURCECACHE_H

#include <string>
#include <unordered_map>
#include "core/system.h"

namespace CodeHero {

class ResourceCache : public System {
public:
    OBJECT(ResourceCache, System);

    explicit ResourceCache(const std::shared_ptr<EngineContext>& iContext)
        : System(iContext) {}

    Error Initialize() override { return Error::OK; }
    Error Cleanup() override { return Error::OK; }

    bool Has(const std::string& iResourcePath) const;
    std::shared_ptr<Object> Get(const std::string& iResourcePath) const;
    void Set(const std::string& iResourcePath, const std::shared_ptr<Object>& iResource);

private:
    std::unordered_map<std::string, std::shared_ptr<Object>> m_Resources;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RESOURCECACHE_H
