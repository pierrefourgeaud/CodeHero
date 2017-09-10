// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_DDS_IMAGECODEC_DDS_H_
#define CODEHERO_DRIVERS_DDS_IMAGECODEC_DDS_H_

#include "core/errors.h"
#include "core/resourcecodec.h"

namespace CodeHero {

class Image;
class FileAccess;

class ImageCodecDDS : public ResourceCodec<Image> {
public:
    OBJECT(ImageCodeDDS, ResourceCodec<Image>)

    ImageCodecDDS(const std::shared_ptr<EngineContext>& iContext);
    ~ImageCodecDDS();

    Error Load(FileAccess& iF, Image& oImage) override;
private:
};

}  // namespace CodeHero

#endif  // CODEHERO_DRIVERS_DDS_IMAGECODEC_DDS_H_
