// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_ASSIMP_MODELCODEC_ASSIMP_H_
#define CODEHERO_DRIVERS_ASSIMP_MODELCODEC_ASSIMP_H_

#include "core/resourcecodec.h"

namespace CodeHero {

class Model;

class ModelCodecAssimp : public ResourceCodec<Model> {
public:
    Error Load(FileAccess& iF, Model& oModel) override;

private:
};

} // namespace CodeHero

#endif // CODEHERO_DRIVERS_ASSIMP_MODELCODEC_ASSIMP_H_
