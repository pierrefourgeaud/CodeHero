// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RESOURCELOADER_H_
#define CODEHERO_CORE_RESOURCELOADER_H_

#include <logger.h>
#include <string>
#include "core/errors.h"
#include "core/object.h"
#include "core/system.h"
#include "core/resourcecodec.h"
#include "core/fileaccess.h"

namespace CodeHero {

template <class T>
class ResourceLoader : public System {
    enum {
        MAX_CODECS = 8
    };

public:
    OBJECT_TEMPLATE(ResourceLoader, T)

    ResourceLoader(std::shared_ptr<EngineContext>& iContext)
        : System(iContext) {}
    virtual ~ResourceLoader() {}
    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;

    Error Initialize() override { return OK; }
    Error Cleanup() override { return OK; }

    Error Load(const std::string& iFilePath, T& oResource) {
        FileAccess f;
        // TODO(pierre) improve error management here
        if (f.Open(iFilePath, FileAccess::READ) == ERR_FILE_NOT_FOUND) {
            LOGE << "ResourceLoader: File not found." << std::endl;
            return ERR_FILE_NOT_FOUND;
        }

        for (int i = 0; i < m_CodecsCount; i++) {
            if (!m_Codecs[i]->RecognizeExt(iFilePath)) {
                continue;
            }

            Error err = m_Codecs[i]->Load(f, oResource);

            // Started to load but an error different than bad image format occured.
            if (err != ERR_IMAGE_FORMAT_UNRECOGNIZED) {
                return err;
            }
        }

        LOGE << "ResourceLoader: File extension not recognized." << std::endl;
        return ERR_IMAGE_FORMAT_UNRECOGNIZED;
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
