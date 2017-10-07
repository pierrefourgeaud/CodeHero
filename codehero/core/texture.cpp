// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/texture.h"
#include "core/assert.h"
#include "core/enginecontext.h"
#include "core/resourceloader.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

Texture::Texture(std::shared_ptr<EngineContext>& iContext)
    : Serializable(iContext) {
    m_Images.resize(numberTextureFaces[m_Type]);
}

Texture::~Texture() {}

void Texture::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Texture);

    CH_OBJECT_ATTRIBUTE(Texture, "Faces", VariantArray, Variant::Value::VVT_Array, nullptr, static_cast<bool(Texture::*)(const std::vector<std::string>&)>(&Texture::Load));
}

std::shared_ptr<Texture> Texture::Create(const std::shared_ptr<EngineContext>& iContext) {
    return iContext->GetSubsystem<RenderSystem>()->CreateTexture();
}

bool Texture::Load(const std::shared_ptr<Image>& iImage) {
    CH_ASSERT(m_Type == T_2D);

    m_Images[0] = iImage;

    return _CreateImpl();
}

bool Texture::Load(const std::string& iImage) {
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

bool Texture::Load(TextureFace iFace, const std::string& iImage) {
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

bool Texture::Load(const std::vector<std::string>& iImages) {
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

void Texture::SetType(Type iType) {
    m_Type = iType;
    m_Images.resize(numberTextureFaces[m_Type]);
}

} // namespace CodeHero
