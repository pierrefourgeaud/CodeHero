// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_IMAGELOADER_H_
#define CODEHERO_CORE_IMAGELOADER_H_

#include <string>
#include "./errors.h"

namespace CodeHero {

// Forward declarations.
class Image;
class ImageCodec;

class ImageLoader
{
    enum {
        MAX_CODECS=8
    };

public:
    virtual ~ImageLoader();
    ImageLoader(const ImageLoader&) = delete;
    ImageLoader& operator=(const ImageLoader&) = delete;

    Error LoadImage(const std::string& iFilePath, Image& oImage);
    bool  AddCodec(ImageCodec* iCodec);

    void ClearCodecs();

    // Singleton
    static ImageLoader* GetInstance();

private:
    ImageCodec* m_Codecs[MAX_CODECS] = {nullptr};
    int         m_CodecsCount = 0;

    // Singleton
    ImageLoader();
    static ImageLoader* m_pInstance;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_IMAGELOADER_H_
