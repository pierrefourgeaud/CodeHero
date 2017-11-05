// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_PNG_IMAGECODEC_PNG_H_
#define CODEHERO_DRIVERS_PNG_IMAGECODEC_PNG_H_

#include "core/errors.h"
#include "core/resourcecodec.h"

namespace CodeHero {

class Image;
class FileAccess;

class ImageCodecPNG : public ResourceCodec<Image> {
public:
    OBJECT(ImageCodePNG, ResourceCodec)

    ImageCodecPNG(const std::shared_ptr<EngineContext>& iContext);
    ~ImageCodecPNG();

    std::shared_ptr<Image> Load(FileAccess& iF, const std::string& iTypeName) override;
private:
};

}  // namespace CodeHero

#endif  // CODEHERO_DRIVERS_PNG_IMAGECODEC_PNG_H_
