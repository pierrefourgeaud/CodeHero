// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_TGA_IMAGECODEC_TGA_H_
#define CODEHERO_DRIVERS_TGA_IMAGECODEC_TGA_H_

#include "core/errors.h"
#include "core/resourcecodec.h"

namespace CodeHero {

// Forward declaration
class Image;
class FileAccess;
struct TGAHeader;

class ImageCodecTGA : public ResourceCodec<Image> {
public:
    OBJECT(ImageCodecTGA, ResourceCodec<Image>)

    ImageCodecTGA(const std::shared_ptr<EngineContext>& iContext);
    ~ImageCodecTGA();

    std::shared_ptr<Image> Load(FileAccess& iF, const std::string& iTypeName) override;

private:
    void _DecodeTGARle(const std::vector<uint8_t>& iCompressedBuffer,
                       size_t iPixelSize,
                       std::vector<uint8_t>& oUncompressedBuffer,
                       size_t iOutputSize);
    std::shared_ptr<Image> _ConvertToImage(const uint8_t* iBuffer,
                                           const TGAHeader& iHeader,
                                           const std::vector<uint8_t>& iPalette,
                                           bool iIsMonochrome);
};

}  // namespace CodeHero

#endif // CODEHERO_DRIVERS_TGA_IMAGECODEC_TGA_H_
