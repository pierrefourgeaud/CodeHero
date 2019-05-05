// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/resourcecache.h"

namespace CodeHero {

bool ResourceCache::Has(const std::string& iResourcePath) const {
    return m_Resources.find(iResourcePath) != m_Resources.end();
}

std::shared_ptr<Object> ResourceCache::Get(const std::string& iResourcePath) const {
    auto resource = m_Resources.find(iResourcePath);

    return resource != m_Resources.end() ? resource->second : nullptr;
}

void ResourceCache::Set(const std::string& iResourcePath,
                        const std::shared_ptr<Object>& iResource) {
    // TODO(pierre) Should we do something if the resource already exists ? (at least the key)
    m_Resources[iResourcePath] = iResource;
}

} // namespace CodeHero
