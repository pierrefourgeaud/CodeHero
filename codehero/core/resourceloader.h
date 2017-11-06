// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RESOURCELOADER_H_
#define CODEHERO_CORE_RESOURCELOADER_H_

#include <logger.h>
#include <string>
#include "core/errors.h"
#include "core/object.h"
#include "core/serializable.h"
#include "core/system.h"
#include "core/resourcecache.h"
#include "core/resourcecodec.h"
#include "core/fileaccess.h"

namespace CodeHero {

template <class T>
class ResourceLoader : public System {
    static_assert(
            std::is_base_of<Object, T>::value,
            "The instance to be loaded must be of type Object.");

    enum {
        MAX_CODECS = 8
    };

public:
    OBJECT_TEMPLATE(ResourceLoader, T, System)

    ResourceLoader(std::shared_ptr<EngineContext>& iContext)
        : System(iContext) {}
    virtual ~ResourceLoader() {}
    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;

    Error Initialize() override { return OK; }
    Error Cleanup() override { return OK; }

    std::shared_ptr<T> Load(const std::string& iFilePath, const std::string& iTypeName = T::GetTypeNameStatic()) const {
        auto resourceCache = m_pContext->GetSubsystem<ResourceCache>();
        auto resource = resourceCache->Get(iFilePath);
        if (resource) {
            if (resource->IsInstanceOf(T::GetTypeInfoStatic())) {
                return std::static_pointer_cast<T>(resource);
            } else {
                LOGE << "[ResourceLoader]: Impossible to cast " << resource->GetTypeName() << " to "
                     << T::GetTypeNameStatic() << "." << std::endl;
                return nullptr;
            }
        }

        FileAccess f;
        // TODO(pierre) improve error management here
        if (f.Open(iFilePath, FileAccess::READ) == ERR_FILE_NOT_FOUND) {
            LOGE << "[ResourceLoader]: File not found." << std::endl;
            return nullptr;
        }

        for (int i = 0; i < m_CodecsCount; i++) {
            if (!m_Codecs[i]->RecognizeExt(iFilePath)) {
                continue;
            }

            auto newResource = m_Codecs[i]->Load(f, iTypeName);

            if (newResource) {
                resourceCache->Set(iFilePath, newResource);
                return newResource;
            } else {
                LOGE << "[ResourceLoader]: An unexpected error occurred, resource not loaded." << std::endl;
                return nullptr;
            }
        }

        LOGE << "ResourceLoader: File extension not recognized." << std::endl;
        return nullptr;
    }

    template <class U>
    std::shared_ptr<U> Load(const std::string& iFilePath) const {
        // TODO(pierre) Do a better job with the error message here...
        static_assert(std::is_base_of<T, U>::value, "T is not base of U.");
        auto res = Load(iFilePath, U::GetTypeNameStatic());
        if (res) {
            return std::static_pointer_cast<U>(res);
        }

        return nullptr;
    }

    bool  AddCodec(ResourceCodec<T>* iCodec) {
        if (m_CodecsCount == MAX_CODECS) {
            LOGE << "ResourceLoader: Cannot add new codec. Maximum number reached." << std::endl;
            return false;
        }

        m_Codecs[m_CodecsCount++] = iCodec;
        return true;
    }

    void ClearCodecs() {
        for (int i = 0; i < MAX_CODECS && m_Codecs[i] != nullptr; ++i) {
            delete m_Codecs[i];
            m_Codecs[i] = nullptr;
        }
    }

private:
    ResourceCodec<T>* m_Codecs[MAX_CODECS] = {nullptr};
    int               m_CodecsCount = 0;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_RESOURCELOADER_H_
