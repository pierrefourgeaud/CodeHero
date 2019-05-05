// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "imagecodec_jpg.h"
#include <jpgd.h>
#include <logger.h>
#include <cstring>
#include <vector>
#include "core/fileaccess.h"
#include "core/image.h"

namespace CodeHero {

ImageCodecJPG::ImageCodecJPG(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Image>(iContext) {
    std::vector<std::string> ext{"jpg", "jpeg"};
    for (auto& e : ext) {
        _AddExtension(e);
    }
}

ImageCodecJPG::~ImageCodecJPG() {}

std::shared_ptr<Image> ImageCodecJPG::Load(FileAccess& iF, const std::string& iTypeName) {
    (void)iTypeName;
    const int32_t size = iF.GetSize();
    ImageData buffer(size);
    iF.Read(&buffer[0], size);

    jpgd::jpeg_decoder_mem_stream memStream(&buffer[0], size);
    jpgd::jpeg_decoder decoder(&memStream);

    if (decoder.get_error_code() != jpgd::JPGD_SUCCESS) {
        LOGE << "JPG: Failed to initialize decoder..." << std::endl;
        return nullptr;
    }

    const int32_t width = decoder.get_width();
    const int32_t height = decoder.get_height();

    int32_t comps = decoder.get_num_components();
    if (comps == 3) {
        comps = 4; // wtf? weird....
    }

    if (decoder.begin_decoding() != jpgd::JPGD_SUCCESS) {
        LOGE << "JPG: Failed to start decoding" << std::endl;
        return nullptr;
    }

    const int32_t dstBpl = width * comps;

    ImageData dest(dstBpl * height);

    jpgd::uint8* imageData = (jpgd::uint8*)&dest[0];

    for (int32_t y = 0; y < height; ++y) {
        const jpgd::uint8* line;
        jpgd::uint lineLen;
        if (decoder.decode((const void**)&line, &lineLen) != jpgd::JPGD_SUCCESS) {
            LOGE << "JPG: Error during decoding, image invalid" << std::endl;
            return nullptr;
        }

        jpgd::uint8* dst = imageData + y * dstBpl;
        std::memcpy(dst, line, dstBpl);
    }

    Image::Format fmt;
    if (comps == 1) {
        fmt = Image::Format::IFMT_Luminance;
    } else {
        fmt = Image::Format::IFMT_RGBA;
    }

    auto image = std::make_shared<Image>(m_pContext);
    image->Create(width, height, dest, fmt);

    return image;
}

} // namespace CodeHero
