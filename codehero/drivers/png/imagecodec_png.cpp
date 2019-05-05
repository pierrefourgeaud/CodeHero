// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "imagecodec_png.h"
#include <logger.h>
#include <png.h>
#include <vector>
#include "core/fileaccess.h"
#include "core/image.h"

namespace CodeHero {

// local function
static void PngErrorFunction(png_structp, png_const_charp iText) {
    LOGE << "ImageCodec_PNG: " << iText << std::endl;
}

static void PngWarnFunction(png_structp, png_const_charp iText) {
    LOGW << "ImageCodec_PNG: " << iText << std::endl;
}

static void PngReadFunction(png_structp iPng, png_bytep iData, png_size_t iLength) {
    FileAccess* f = static_cast<FileAccess*>(png_get_io_ptr(iPng));
    f->Read(iData, iLength);
}

ImageCodecPNG::ImageCodecPNG(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Image>(iContext) {
    std::vector<std::string> ext{"png"};
    for (auto& e : ext) {
        _AddExtension(e);
    }
}

ImageCodecPNG::~ImageCodecPNG() {}

std::shared_ptr<Image> ImageCodecPNG::Load(FileAccess& iF, const std::string& iTypeName) {
    (void)iTypeName;
    png_structp png;
    png_infop info;

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, PngErrorFunction,
                                 PngWarnFunction);

    if (png == nullptr) {
        LOGE << "ImageCodecPNG: Could not create read structure." << std::endl;
        return nullptr;
    }

    info = png_create_info_struct(png);
    if (info == nullptr) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        LOGE << "ImageCodecPNG: Could not create info structure." << std::endl;
        return nullptr;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        LOGE << "ImageCodecPNG: Could not initialize buffer." << std::endl;
        return nullptr;
    }

    png_set_read_fn(png, (void*)&iF, PngReadFunction);

    png_read_info(png, info);

    png_uint_32 width, height;
    int depth, color;

    png_get_IHDR(png, info, &width, &height, &depth, &color, nullptr, nullptr, nullptr);

    if (depth < 8) { // only bit dept 8 per channel is handled
        png_set_packing(png);
    } else if (depth > 8) {
        png_set_strip_16(png);
        png_read_update_info(png, info);
    }

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
        png_read_update_info(png, info);
        png_get_IHDR(png, info, &width, &height, &depth, &color, nullptr, nullptr, nullptr);
    }

    int palette_colors = 0;
    int palette_components = 0;
    int components = 0;

    Image::Format fmt;
    switch (color) {
        case PNG_COLOR_TYPE_GRAY: fmt = Image::IFMT_Grayscale; break;
        case PNG_COLOR_TYPE_GRAY_ALPHA: fmt = Image::IFMT_GrayscaleAlpha; break;
        case PNG_COLOR_TYPE_RGB: fmt = Image::IFMT_RGB; break;
        case PNG_COLOR_TYPE_RGB_ALPHA: fmt = Image::IFMT_RGBA; break;
        case PNG_COLOR_TYPE_PALETTE: {
            int ntrans = 0;
            png_get_tRNS(png, info, nullptr, &ntrans, nullptr);

            fmt = ntrans > 0 ? Image::IFMT_IndexedAlpha : Image::IFMT_Indexed;
            palette_components = ntrans > 0 ? 4 : 3;

            png_colorp colors;
            png_get_PLTE(png, info, &colors, &palette_colors);

        } break;
        default:
            LOGE << "ImageCodecPNG: Invalid PNG type." << std::endl;
            png_destroy_read_struct(&png, &info, nullptr);
            return nullptr;
    }
    components = Image::GetComponentsFromFormat(fmt);

    int rowsize = components * width;
    ImageData dest(rowsize * height + palette_components * 256);

    uint8_t* data = &dest[0];
    uint8_t** rows = new uint8_t*[height];

    for (unsigned int i = 0; i < height; ++i) {
        rows[i] = &data[components * width * i];
    }

    png_read_image(png, static_cast<png_bytep*>(rows));

    // TODO(pierre) Manipulations to do with palette here, for later

    auto image = std::make_shared<Image>(m_pContext);
    image->Create(width, height, dest, fmt);

    delete[] rows;
    png_destroy_read_struct(&png, &info, nullptr);

    return image;
}

} // namespace CodeHero
