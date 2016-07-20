// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./core/image.h"
#include "./core/logging/Logger.h"

namespace CodeHero {

Image::Image() {}

Image::Image(uint32_t iWidth, uint32_t iHeight, const ImageData& iData, Image::Format iFmt) {
    Create(iWidth, iHeight, iData, iFmt);
}

void Image::Create(uint32_t iWidth, uint32_t iHeight, const ImageData& iData, Image::Format iFmt) {
    m_Width = iWidth;
    m_Height = iHeight;
    m_Data = iData;
    m_Fmt = iFmt;
}

// statics
int Image::GetComponentsFromFormat(Image::Format iFmt) {
    switch (iFmt) {
    case IFMT_GRAYSCALE:
    case IFMT_INDEXED_ALPHA:
    case IFMT_INDEXED:
        return 1;
    case IFMT_GRAYSCALE_ALPHA:
        return 2;
    case IFMT_RGB:
        return 3;
    case IFMT_RGBA:
        return 4;
    default:
        LOGE << "Image::GetComponentsFromFormat: Format not recognized." << std::endl;
        return -1;
    }
}

}  // namespace CodeHero
