// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./core/texture.h"
#include "./core/imageloader.h"

namespace CodeHero {

Texture::Texture() {}

Texture::~Texture() {}

void Texture::Use() {}

bool Texture::Load(const Image& iImage) {
    m_Image = iImage;

    return _CreateImpl();
}

bool Texture::Load(const char* iImage) {
    ImageLoader* imageLoader = ImageLoader::GetInstance();
    imageLoader->LoadImage(iImage, m_Image);

    return _CreateImpl();
}

} // namespace CodeHero