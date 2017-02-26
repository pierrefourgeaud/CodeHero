// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TEXTURE_H_
#define CODEHERO_CORE_TEXTURE_H_

#include <glad/glad.h>
#include <memory>
#include "core/gpuobject.h"
#include "core/image.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

class Texture : public GPUObject {
public:
    Texture(std::shared_ptr<EngineContext>& iContext);
    virtual ~Texture();

    void Use();
    bool Load(const Image& iImage);
    bool Load(const char* iImage);

protected:
    virtual bool _CreateImpl() = 0;

    Image& _GetRawImage() { return m_Image; }

private:
    std::shared_ptr<EngineContext> m_pContext;
    Image m_Image;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TEXTURE_H_
