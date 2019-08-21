// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_IMAGE_H_
#define CODEHERO_CORE_IMAGE_H_

#include <vector>
#include "core/object.h"
#include "core/typedefs.h"

namespace CodeHero {

using ImageData = std::vector<uint8_t>;

class Image : public Object {
public:
    OBJECT(Image, Object)

    enum Format {
        IFMT_Luminance,      // one byte
        IFMT_Grayscale,      // one byte per pixel, 0-255
        IFMT_Intensity,      // one byte per pixel, 0-255
        IFMT_GrayscaleAlpha, // two bytes per pixel, 0-255. alpha 0-255
        IFMT_RGB,            // one byte R, one byte G, one byte B
        IFMT_RGBA,           // one byte R, one byte G, one byte B, one byte A
        IFMT_Indexed,        // index byte 0-256, and after image end, 256*3 bytes of palette
        IFMT_IndexedAlpha, // index byte 0-256, and after image end, 256*4 bytes of palette (alpha)
        IFMT_DXT1,
        IFMT_DXT3,
        IFMT_DXT5,
        IFMT_Max
    };

    // Create an empty image
    explicit Image(const std::shared_ptr<EngineContext>& iContext);

    void Create(uint32_t iWidth, uint32_t iHeight, Format iFmt = IFMT_Grayscale);
    void Create(uint32_t iWidth, uint32_t iHeight, const ImageData& iData, Format iFmt);

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }
    Format GetFormat() const { return m_Fmt; }
    uint32_t GetSize() const { return m_Data.size(); }

    static int GetComponentsFromFormat(Format iFmt);

    uint8_t* GetRawData() { return m_Data.empty() ? nullptr : &m_Data[0]; }

private:
    ImageData m_Data;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    Format m_Fmt;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_IMAGE_H_
