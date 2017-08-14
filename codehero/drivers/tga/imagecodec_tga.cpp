// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "imagecodec_tga.h"
#include <vector>
#include "core/image.h"
#include "core/fileaccess.h"
#include <logger.h>

// Inspired from GODOT Game Engine TGA Codec

#define TGA_PUT_PIXEL(in, r, g, b, a) \
    int image_data_ofs = ((y * width) + x); \
    in[image_data_ofs * 4 + 0] = r; \
    in[image_data_ofs * 4 + 1] = g; \
    in[image_data_ofs * 4 + 2] = b; \
    in[image_data_ofs * 4 + 3] = a;

namespace CodeHero {

enum TGAType {
    TGAT_NoData = 0,
    TGAT_Indexed = 1,
    TGAT_RGB = 2,
    TGAT_Monochrome = 3,
    TGAT_RLEIndexed = 9,
    TGAT_RLERGB = 10,
    TGAT_RLEMonochrome = 11
};

enum TGAOrigin {
    TGAO_BottomLeft = 0x00,
    TGAO_BottomRight = 0x01,
    TGAO_TopLeft = 0x02,
    TGAO_TopRight = 0x03,
    TGAO_Shift = 0x04,
    TGAO_Mask = 0x30
};

struct TGAHeader {
    uint8_t idLength;
    uint8_t colorMapType;
    TGAType type;

    uint16_t firstColorEntry;
    uint16_t colorMapLength;
    uint8_t colorMapDepth;

    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t pixelDepth;
    uint8_t imageDescriptor;
};

ImageCodecTGA::ImageCodecTGA(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Image>(iContext) {
    std::vector<std::string> ext{"tga", "TGA"};
    for (auto& e : ext) {
        _AddExtension(e);
    }
}

ImageCodecTGA::~ImageCodecTGA() {}

Error ImageCodecTGA::Load(FileAccess& iF, Image& oImage) {
    std::vector<uint8_t> srcImage;
    int srcImageLen = iF.GetSize();

    if (srcImageLen == 0 || srcImageLen < sizeof(TGAHeader)) {
        return Error::ERR_IMAGE_INVALID;
    }

    srcImage.resize(srcImageLen);

    TGAHeader tgaHeader;
    tgaHeader.idLength = iF.Read8();
    tgaHeader.colorMapType = iF.Read8();
    tgaHeader.type = static_cast<TGAType>(iF.Read8());
    tgaHeader.firstColorEntry = iF.Read16();
    tgaHeader.colorMapLength = iF.Read16();
    tgaHeader.colorMapDepth = iF.Read8();
    tgaHeader.xOrigin = iF.Read16();
    tgaHeader.yOrigin = iF.Read16();
    tgaHeader.width = iF.Read16();
    tgaHeader.height = iF.Read16();
    tgaHeader.pixelDepth = iF.Read8();
    tgaHeader.imageDescriptor = iF.Read8();

    bool isEncoded = (tgaHeader.type == TGAT_RLEIndexed || tgaHeader.type == TGAT_RLERGB || tgaHeader.type == TGAT_RLEMonochrome);
    bool hasColorMap = (tgaHeader.type == TGAT_RLEIndexed || tgaHeader.type == TGAT_Indexed);
    bool isMonochrome = (tgaHeader.type == TGAT_RLEMonochrome || tgaHeader.type == TGAT_Monochrome);

    if (tgaHeader.type == TGAT_NoData) {
        return FAILED;
    }

    if (hasColorMap) {
        if (tgaHeader.colorMapLength > 256 || (tgaHeader.colorMapDepth != 24) || tgaHeader.colorMapType != 1) {
            return FAILED;
        }
    } else { 
        if (tgaHeader.colorMapType) {
            return FAILED;
        }
    }

    if (tgaHeader.width <= 0 || tgaHeader.height <= 0) {
        return FAILED;
    }

    if (tgaHeader.pixelDepth != 8 && tgaHeader.pixelDepth != 24 && tgaHeader.pixelDepth != 32) {
        return FAILED;
    }

    iF.Seek(iF.GetPos() + tgaHeader.idLength);

    std::vector<uint8_t> palette;

    if (hasColorMap) {
        size_t colorMapSize = tgaHeader.colorMapLength * (tgaHeader.colorMapDepth >> 3);
        palette.resize(colorMapSize);

        iF.Read(&palette[0], colorMapSize);
    }

    iF.Read(&srcImage[0], srcImageLen - iF.GetPos());

    const size_t pixelSize = tgaHeader.pixelDepth >> 3;
    const size_t bufferSize = (tgaHeader.width * tgaHeader.height) * pixelSize;

    std::vector<uint8_t> uncompressedBuffer;
    uncompressedBuffer.resize(bufferSize);

    const uint8_t* buffer = nullptr;

    if (isEncoded) {
        _DecodeTGARle(srcImage, pixelSize, uncompressedBuffer, bufferSize);
        buffer = &uncompressedBuffer[0];
    } else {
        buffer = &srcImage[0];
    }

    Error err = _ConvertToImage(oImage, buffer, tgaHeader, palette, isMonochrome);

    iF.Close();

    return err;
}

void ImageCodecTGA::_DecodeTGARle(const std::vector<uint8_t>& iCompressedBuffer,
                                  size_t iPixelSize,
                                  std::vector<uint8_t>& oUncompressedBuffer,
                                  size_t iOutputSize) {
    std::vector<uint8_t> pixels;
    pixels.resize(iPixelSize);

    size_t compressedPos = 0;
    size_t outputPos = 0;
    size_t c = 0;
    size_t count = 0;

    while (outputPos < iOutputSize) {
        c = iCompressedBuffer[compressedPos];
        compressedPos += 1;
        count = (c & 0x7f) + 1;

        if (c & 0x80) {
            for (int i = 0; i < iPixelSize; ++i) {
                pixels[i] = iCompressedBuffer[compressedPos];
                compressedPos += 1;
            }
            for (int i = 0; i < count; ++i) {
                for (int j = 0; j < iPixelSize; ++j) {
                    oUncompressedBuffer[outputPos + j] = pixels[j];
                }
                outputPos += iPixelSize;
            }
        } else {
            count *= iPixelSize;
            for (int i = 0; i < count; ++i) {
                oUncompressedBuffer[outputPos] = iCompressedBuffer[compressedPos];
                compressedPos += 1;
                outputPos += 1;
            }
        }
    }
}

Error ImageCodecTGA::_ConvertToImage(Image& oImage,
                                     const uint8_t* iBuffer,
                                     const TGAHeader& iHeader,
                                     const std::vector<uint8_t>& iPalette,
                                     bool iIsMonochrome) {
    uint32_t width = iHeader.width;
    uint32_t height = iHeader.height;
    TGAOrigin origin = static_cast<TGAOrigin>((iHeader.imageDescriptor & TGAO_Mask) >> TGAO_Shift);

    uint32_t xStart;
    int32_t xStep;
    uint32_t xEnd;
    uint32_t yStart;
    int32_t yStep;
    uint32_t yEnd;

    if (origin == TGAO_TopLeft || origin == TGAO_BottomLeft) {
        xStart = 0;
        xStep = 1;
        xEnd = width;
    } else {
        xStart = width - 1;
        xStep = -1;
        xEnd = -1;
    }

    if (origin == TGAO_TopLeft || origin == TGAO_TopRight) {
        yStart = 0;
        yStep = 1;
        yEnd = height;
    } else {
        yStart = height - 1;
        yStep = -1;
        yEnd = -1;
    }

    std::vector<uint8_t> imageData;
    imageData.resize(width * height * sizeof(uint32_t));

    size_t i = 0;
    uint32_t x = xStart;
    uint32_t y = yStart;

    if (iHeader.pixelDepth == 8) {
        if (iIsMonochrome) {
            while (y != yEnd) {
                while (x != xEnd) {
                    uint8_t shade = iBuffer[i];

                    TGA_PUT_PIXEL(imageData, shade, shade, shade, 0xff)

                        x += xStep;
                    i += 1;
                }
                x = xStart;
                y += yStep;
            }
        } else {
            while (y != yEnd) {
                while (x != xEnd) {
                    uint8_t index = iBuffer[i];
                    uint8_t r = 0x00;
                    uint8_t g = 0x00;
                    uint8_t b = 0x00;
                    uint8_t a = 0xff;

                    if (iHeader.colorMapDepth == 24) {
                        r = (iPalette[(index * 3) + 0]);
                        g = (iPalette[(index * 3) + 1]);
                        b = (iPalette[(index * 3) + 2]);
                    }
                    else {
                        return ERR_IMAGE_INVALID;
                    }

                    TGA_PUT_PIXEL(imageData, r, g, b, a)

                        x += xStep;
                    i += 1;
                }
                x = xStart;
                y += yStep;
            }
        }
    } else if (iHeader.pixelDepth == 24) {
        while (y != yEnd) {
            while (x != xEnd) {
                uint8_t r = iBuffer[i + 2];
                uint8_t g = iBuffer[i + 1];
                uint8_t b = iBuffer[i + 0];

                TGA_PUT_PIXEL(imageData, r, g, b, 0xff)

                    x += xStep;
                i += 3;
            }
            x = xStart;
            y += yStep;
        }
    } else if (iHeader.pixelDepth == 32) {
        while (y != yEnd) {
            while (x != xEnd) {
                uint8_t a = iBuffer[i + 3];
                uint8_t r = iBuffer[i + 2];
                uint8_t g = iBuffer[i + 1];
                uint8_t b = iBuffer[i + 0];

                TGA_PUT_PIXEL(imageData, r, g, b, a)

                    x += xStep;
                i += 4;
            }
            x = xStart;
            y += yStep;
        }
    }

    oImage.Create(width, height, imageData, Image::IFMT_RGBA);

    return OK;
}

}  // namespace CodeHero
