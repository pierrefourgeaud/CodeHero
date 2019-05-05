// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RESOURCECODEC_H_
#define CODEHERO_CORE_RESOURCECODEC_H_

#include <string>
#include <vector>
#include "core/errors.h"
#include "core/object.h"
#include "core/utils.h"

namespace CodeHero {

// Forward declaration
class FileAccess;

template <class T>
class ResourceCodec : public Object {
   public:
    OBJECT_TEMPLATE(ResourceCodec, T, Object)

    ResourceCodec(const std::shared_ptr<EngineContext>& iContext) : Object(iContext) {}
    virtual ~ResourceCodec() {}
    ResourceCodec(const ResourceCodec&) = delete;
    ResourceCodec& operator=(const ResourceCodec&) = delete;

    bool RecognizeExt(const std::string& iFilePath) {
        for (size_t i = 0; i < m_Extensions.size(); ++i) {
            if (EndsWith(LowerCased(iFilePath), LowerCased(m_Extensions[i]))) {
                return true;
            }
        }

        return false;
    }

    virtual std::shared_ptr<T> Load(FileAccess& iF, const std::string& iTypeName) = 0;

   protected:
    void _AddExtension(const std::string& iExtension) { m_Extensions.push_back(iExtension); }

   private:
    std::vector<std::string> m_Extensions;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RESOURCECODEC_H_
