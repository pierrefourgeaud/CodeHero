// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TEXTURE_H_
#define CODEHERO_CORE_TEXTURE_H_

#include <glad/glad.h>
#include "./core/image.h"

namespace CodeHero {

class Texture {
public:
    Texture();
    virtual ~Texture();

    void Use();
    bool Load(const Image& iImage);
    bool Load(const char* iImage);

protected:
    virtual void _CreateImpl() = 0;

    Image& _GetRawImage() { return m_Image; }

private:
    Image m_Image;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TEXTURE_H_
