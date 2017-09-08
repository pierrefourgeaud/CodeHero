// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/texture.h"
#include "core/assert.h"
#include "core/resourceloader.h"
#include "core/enginecontext.h"

namespace CodeHero {

Texture::Texture(std::shared_ptr<EngineContext>& iContext, Type iType)
    : m_Type(iType)
    , m_pContext(iContext) {
    m_Images.resize(numberTextureFaces[iType]);
}

Texture::~Texture() {}

bool Texture::Load(const std::shared_ptr<Image>& iImage) {
    CH_ASSERT(m_Type == T_2D);

    m_Images[0] = iImage;

    return _CreateImpl();
}

bool Texture::Load(const char* iImage) {
    CH_ASSERT(m_Type == T_2D);

    m_Images[0] = std::make_shared<Image>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImage, *m_Images[0]);

    return _CreateImpl();
}

bool Texture::Load(TextureFace iFace, const std::shared_ptr<Image>& iImage) {
    CH_ASSERT(numberTextureFaces[m_Type] > iFace);

    m_Images[iFace] = iImage;

    return _CreateImpl();
}

bool Texture::Load(TextureFace iFace, const char* iImage) {
    CH_ASSERT(numberTextureFaces[m_Type] > iFace);

    m_Images[iFace] = std::make_shared<Image>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImage, *m_Images[iFace]);

    return _CreateImpl();
}

bool Texture::Load(const std::vector<std::shared_ptr<Image>>& iImages) {
    CH_ASSERT(numberTextureFaces[m_Type] == iImages.size());

    m_Images = iImages;

    return _CreateImpl();
}

bool Texture::Load(const std::vector<const char*>& iImages) {
    CH_ASSERT(numberTextureFaces[m_Type] == iImages.size());

    size_t nbImages = iImages.size();
    for (size_t i = 0; i < nbImages; ++i) {
        m_Images[i] = std::make_shared<Image>(m_pContext);
        m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImages[i], *m_Images[i]);
    }

    return _CreateImpl();
}

void Texture::SetWrapMode(TextureCoordinate iCoordinate, TextureWrapMode iWrapMode) {
    m_WrapCoordinates[iCoordinate] = iWrapMode;
}

} // namespace CodeHero
