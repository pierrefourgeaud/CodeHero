// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/texture.h"
#include "core/resourceloader.h"
#include "core/enginecontext.h"

namespace CodeHero {

Texture::Texture(std::shared_ptr<EngineContext>& iContext)
    : m_pContext(iContext)
    , m_Image(iContext) {}

Texture::~Texture() {}

bool Texture::Load(const Image& iImage) {
    m_Image = iImage;

    return _CreateImpl();
}

bool Texture::Load(const char* iImage) {
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImage, m_Image);

    return _CreateImpl();
}

} // namespace CodeHero
