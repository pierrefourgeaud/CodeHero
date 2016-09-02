// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./imageloader.h"
#include "./imagecodec.h"
#include "./fileaccess.h"
#include <logger.h>

namespace CodeHero {

ImageLoader* ImageLoader::m_pInstance = nullptr;

ImageLoader::~ImageLoader() {
    delete m_pInstance;
    m_pInstance = nullptr;
}

Error ImageLoader::LoadImage(const std::string& iFilePath, Image& oImage) {
    FileAccess f;
    // TODO(pierre) improve error management here
    if (f.Open(iFilePath, FileAccess::READ) == ERR_FILE_NOT_FOUND) {
        LOGE << "ImageLoader: File not found." << std::endl;
        return ERR_FILE_NOT_FOUND;
    }

    for (int i = 0; i < m_CodecsCount; i++) {
        if (!m_Codecs[i]->RecognizeExt(iFilePath)) {
            continue;
        }

        Error err = m_Codecs[i]->LoadImage(f, oImage);

        // Started to load but an error different than bad image format occured.
        if (err != ERR_IMAGE_FORMAT_UNRECOGNIZED) {
            return err;
        }
    }

    LOGE << "ImageLoader: File not found." << std::endl;
    return ERR_IMAGE_FORMAT_UNRECOGNIZED;
}

bool ImageLoader::AddCodec(ImageCodec* iCodec) {
    if (m_CodecsCount == MAX_CODECS) {
        LOGE << "ImageLoader: Cannot add new codec. Maximum number reached." << std::endl;
        return false;
    }

    m_Codecs[m_CodecsCount++] = iCodec;
    return true;
}

void ImageLoader::ClearCodecs() {
    for (int i = 0; i < MAX_CODECS && m_Codecs[i] != nullptr; ++i) {
        delete m_Codecs[i];
        m_Codecs[i] = nullptr;
    }
}

ImageLoader* ImageLoader::GetInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new ImageLoader();
    }

    return m_pInstance;
}

// Private
ImageLoader::ImageLoader() {}


}  // namespace CodeHero
