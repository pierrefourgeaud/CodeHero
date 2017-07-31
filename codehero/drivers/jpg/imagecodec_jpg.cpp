// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <jpgd.h>
#include "imagecodec_jpg.h"
#include "core/image.h"
#include "core/fileaccess.h"
#include <logger.h>

namespace CodeHero {

ImageCodecJPG::ImageCodecJPG(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Image>(iContext) {
    _AddExtension("jpg");
    _AddExtension("jpeg");
}

ImageCodecJPG::~ImageCodecJPG() {}

Error ImageCodecJPG::Load(FileAccess& iF, Image& oImage) {
    const int32_t size = iF.GetSize();
    ImageData buffer(size);
    iF.Read(&buffer[0], size);

    jpgd::jpeg_decoder_mem_stream memStream(&buffer[0], size);
    jpgd::jpeg_decoder decoder(&memStream);

    if (decoder.get_error_code() != jpgd::JPGD_SUCCESS) {
        LOGE << "JPG: Failed to initialize decoder..." << std::endl;
        return Error::ERR_CANT_OPEN;
    }

    const int32_t width = decoder.get_width();
    const int32_t height = decoder.get_height();

    int32_t comps = decoder.get_num_components();
    if (comps == 3) {
        comps = 4; // wtf? weird....
    }

    if (decoder.begin_decoding() != jpgd::JPGD_SUCCESS) {
        LOGE << "JPG: Failed to start decoding" << std::endl;
        return Error::ERR_IMAGE_INVALID;
    }

    const int32_t dstBpl = width * comps;

    ImageData dest(dstBpl * height);

    jpgd::uint8* imageData = (jpgd::uint8*)&dest[0];

    for (int32_t y = 0; y < height; ++y) {
        const jpgd::uint8* line;
        jpgd::uint lineLen;
        if (decoder.decode((const void**)&line, &lineLen) != jpgd::JPGD_SUCCESS) {
            LOGE << "JPG: Error during decoding, image invalid" << std::endl;
            return ERR_IMAGE_INVALID;
        }

        jpgd::uint8* dst = imageData + y * dstBpl;
        memcpy(dst, line, dstBpl);
    }

    Image::Format fmt;
    if (comps == 1) {
        fmt = Image::Format::IFMT_Luminance;
    } else {
        fmt = Image::Format::IFMT_RGBA;
    }

    oImage.Create(width, height, dest, fmt);

    return OK;
}

}  // namespace CodeHero
