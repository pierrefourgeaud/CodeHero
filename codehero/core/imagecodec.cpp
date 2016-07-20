// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./core/imagecodec.h"
#include "./core/utils.h"

namespace CodeHero {

bool ImageCodec::RecognizeExt(const std::string& iFilePath) {
    for (size_t i = 0; i < m_Extensions.size(); ++i) {
        if (EndsWith(iFilePath, m_Extensions[i])) {
            return true;
        }
    }

    return false;
}

void ImageCodec::_AddExtension(const std::string& iExtension) {
    m_Extensions.push_back(iExtension);
}

}  // namespace CodeHero
