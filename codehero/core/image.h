// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_IMAGE_H_
#define CODEHERO_CORE_IMAGE_H_

#include <vector>
#include "./core/typedefs.h"

namespace CodeHero {

using ImageData = std::vector<uint8_t>;

class Image {
public:
    enum Format {
        IFMT_GRAYSCALE, // one byte per pixel, 0-255
        IFMT_INTENSITY, // one byte per pixel, 0-255
        IFMT_GRAYSCALE_ALPHA, // two bytes per pixel, 0-255. alpha 0-255
        IFMT_RGB, // one byte R, one byte G, one byte B
        IFMT_RGBA, // one byte R, one byte G, one byte B, one byte A
        IFMT_INDEXED, // index byte 0-256, and after image end, 256*3 bytes of palette
        IFMT_INDEXED_ALPHA, // index byte 0-256, and after image end, 256*4 bytes of palette (alpha)
        IFMT_MAX
    };

    // Create an empty image
    Image();

    // Create image with data
    Image(uint32_t iWidth, uint32_t iHeight, const ImageData& iData, Format iFmt);

    void Create(uint32_t iWidth, uint32_t iHeight, const ImageData& iData, Format iFmt);

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    static int GetComponentsFromFormat(Format iFmt);

    uint8_t* GetRawData() { return &m_Data[0]; }

private:
    ImageData m_Data;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    Format m_Fmt;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_IMAGE_H_
