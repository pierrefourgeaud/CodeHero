// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_IMAGECODEC_H_
#define CODEHERO_CORE_IMAGECODEC_H_

#include <string>
#include <vector>
#include "./core/errors.h"

namespace CodeHero {

// Forward declarations.
class Image;
class FileAccess;

class ImageCodec {
public:
    ImageCodec() {}
    virtual ~ImageCodec() {}
    ImageCodec(const ImageCodec&) = delete;
    ImageCodec& operator=(const ImageCodec&) = delete;

    bool RecognizeExt(const std::string& iFilePath);
    virtual Error LoadImage(FileAccess& iF, Image& oImage) = 0;

protected:
    void _AddExtension(const std::string& iExtension);

private:
    std::vector<std::string> m_Extensions;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_IMAGECODEC_H_
