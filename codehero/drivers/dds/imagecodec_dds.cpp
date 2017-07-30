// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "drivers/dds/imagecodec_dds.h"
#include <map>
#include "core/image.h"
#include "core/fileaccess.h"
#include <logger.h>

struct DDS_PIXELFORMAT {
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwFourCC;
    uint32_t dwRGBBitCount;
    uint32_t dwRBitMask;
    uint32_t dwGBitMask;
    uint32_t dwBBitMask;
    uint32_t dwABitMask;
};

struct DDS_HEADER {
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwHeight;
    uint32_t dwWidth;
    uint32_t dwPitchOrLinearSize;
    uint32_t dwDepth;
    uint32_t dwMipMapCount;
    uint32_t dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    uint32_t dwCaps1;
    uint32_t dwCaps2;
    uint32_t dwReserved2[3];
};

enum DDSPixelFormatFlags {
    DDSPFF_ALPHAPIXELS = 0x00000001,
    DDSPFF_FOURCC = 0x00000004,
    DDSPFF_RGB = 0x00000040,
    DDSPFF_RGBA = 0x00000041
};

enum DDSTextureCompressedFlags {
    DDSTCF_FOURCC_DXT1 = 0x31545844, // (MAKEFOURCC('D','X','T','1'))
    DDSTCF_FOURCC_DXT3 = 0x33545844, // (MAKEFOURCC('D','X','T','3'))
    DDSTCF_FOURCC_DXT5 = 0x35545844  // (MAKEFOURCC('D','X','T','5'))
};

enum DDSFormat {
    DDS_DXT1,
    DDS_DXT3,
    DDS_DXT5,
    // DDS_ATI1,
    // DDS_ATI2,
    DDS_BGRA8,
    DDS_BGR8,
    DDS_RGBA8, // flipped in dds
    DDS_RGB8,  // flipped in dds
    // DDS_BGR5A1,
    // DDS_BGR565,
    // DDS_BGR10A2,
    // DDS_INDEXED,
    // DDS_LUMINANCE,
    // DDS_LUMINANCE_ALPHA,
    DDS_MAX
};

std::map<DDSFormat, CodeHero::Image::Format> formatMapping = {
    {DDSFormat::DDS_RGB8, CodeHero::Image::Format::IFMT_RGB},
    {DDSFormat::DDS_RGBA8, CodeHero::Image::Format::IFMT_RGBA},
    {DDSFormat::DDS_DXT1, CodeHero::Image::Format::IFMT_DXT1},
    {DDSFormat::DDS_DXT3, CodeHero::Image::Format::IFMT_DXT3},
    {DDSFormat::DDS_DXT5, CodeHero::Image::Format::IFMT_DXT5},
};

namespace CodeHero {

bool IsCompressed(DDSFormat iFormat) {
    return (iFormat == DDS_DXT1 ||
            iFormat == DDS_DXT3 ||
            iFormat == DDS_DXT5);
}

ImageCodecDDS::ImageCodecDDS(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Image>(iContext) {
    _AddExtension("dds");
}

ImageCodecDDS::~ImageCodecDDS() {}

std::string FourCC(uint32_t iEnc) {
    std::string fourcc(4, '\0');
    fourcc[0] = iEnc >> 0 & 0xFF;
    fourcc[1] = iEnc >> 8 & 0xFF;
    fourcc[2] = iEnc >> 16 & 0xFF;
    fourcc[3] = iEnc >> 24 & 0xFF;
    return fourcc;
}

Error ImageCodecDDS::Load(FileAccess& iF, Image& oImage) {
    // Confirm that the file seems to be DDS
    uint32_t magic = iF.Read32();
    if (FourCC(magic) != "DDS ") {
        LOGE << "DDS: Format of texture does not seem to be valid." << std::endl;
        return Error::ERR_IMAGE_INVALID;
    }

    // Read DDS HEADER
    DDS_HEADER header;
    iF.Read((uint8_t*)&header, sizeof(DDS_HEADER));

    // TODO(pierre) Check what kind of texture it might be
    // when this is implemented in the engine (header.dwCaps2)
    // DDSF_CUBEMAP or DDSF_VOLUME

    DDSFormat ddsFormat;
    if (header.ddspf.dwFlags & DDSPFF_FOURCC) {
        switch (header.ddspf.dwFourCC) {
        case DDSTCF_FOURCC_DXT1:
            ddsFormat = DDS_DXT1;
            break;
        case DDSTCF_FOURCC_DXT3:
            ddsFormat = DDS_DXT3;
            break;
        case DDSTCF_FOURCC_DXT5:
            ddsFormat = DDS_DXT5;
            break;
        default:
            LOGE << "DDS: Unknown texture compression '"
                 << FourCC(header.ddspf.dwFourCC) << "'" << std::endl;
            return Error::ERR_IMAGE_INVALID;
        }
    } else if (header.ddspf.dwFlags & DDSPFF_RGB) {
        if (header.ddspf.dwRGBBitCount == 24 &&
            header.ddspf.dwRBitMask == 0x00ff0000 &&
            header.ddspf.dwGBitMask == 0x0000ff00 &&
            header.ddspf.dwBBitMask == 0x000000ff) {
            ddsFormat = DDS_BGR8;
        } else if (header.ddspf.dwRGBBitCount == 24 &&
                   header.ddspf.dwRBitMask == 0x000000ff &&
                   header.ddspf.dwGBitMask == 0x0000ff00 &&
                   header.ddspf.dwBBitMask == 0x00ff0000) {
            ddsFormat = DDS_RGB8;
        }
    } else if (header.ddspf.dwFlags & DDSPFF_RGBA) {
        if (header.ddspf.dwRGBBitCount == 32 &&
            header.ddspf.dwRBitMask == 0x00ff0000 &&
            header.ddspf.dwGBitMask == 0x0000ff00 &&
            header.ddspf.dwBBitMask == 0x000000ff &&
            header.ddspf.dwABitMask == 0xff000000) {
            ddsFormat = DDS_BGRA8;
        }
        else if (header.ddspf.dwRGBBitCount == 32 &&
            header.ddspf.dwRBitMask == 0x000000ff &&
            header.ddspf.dwGBitMask == 0x0000ff00 &&
            header.ddspf.dwBBitMask == 0x00ff0000 &&
            header.ddspf.dwABitMask == 0xff000000) {
            ddsFormat = DDS_RGBA8;
        }
    } else {
        LOGE << "DDS: Unrecognized texture format." << std::endl;
        return Error::ERR_IMAGE_FORMAT_UNRECOGNIZED;
    }

    bool compressed = IsCompressed(ddsFormat);
    uint32_t width = header.dwWidth;
    uint32_t height = header.dwHeight;
    uint32_t size;
    if (compressed) {
        size = ((width + 3) / 4) * ((height + 3) / 4) * (ddsFormat == DDS_DXT1 ? 8 : 16);
    } else {
        size = width * height * Image::GetComponentsFromFormat(formatMapping[ddsFormat]);
    }

    ImageData dest(size);
    iF.Read(&dest[0], size);

    oImage.Create(width, height, dest, formatMapping[ddsFormat]);

    // TODO(pierre) The mipmaps are not generated and or used here. It should probably be...
    // TODO(pierre) The format BGRA... are not compatible, we should convert them somehow...

    return OK;
}

}  // namespace CodeHero
