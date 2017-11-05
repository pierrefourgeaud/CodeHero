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

static std::string TypeToString(Texture::Type iType) {
    CH_ASSERT(iType < Texture::Type::T_Max);

    switch (iType) {
    case Texture::Type::T_2D: return "T_2D";
    case Texture::Type::T_Cube: return "T_Cube";
    default:
        LOGE << "[Texture]: Failed to convert enum type, it seems that the enum is not valid..." << std::endl;
        CH_ASSERT(false);
        return "T_2D";
    }
}

static Texture::Type TypeFromString(const std::string& iEnumValue) {
    if (iEnumValue == "T_2D") {
        return Texture::Type::T_2D;
    } else if (iEnumValue == "T_Cube") {
        return Texture::Type::T_Cube;
    }

    LOGE << "[Texture]: Failed to apply type, '" << iEnumValue << "' is invalid. Ignored." << std::endl;
    CH_ASSERT(false);
    return Texture::Type::T_2D;
}

Texture::Texture(std::shared_ptr<EngineContext>& iContext)
    : Serializable(iContext) {
    m_Images.resize(numberTextureFaces[m_Type]);
}

Texture::~Texture() {}

void Texture::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Texture);

    CH_OBJECT_ATTRIBUTE_ENUM(Texture, "Type", Texture::Type, &Texture::GetType, &Texture::SetType, TypeFromString, TypeToString);
    CH_OBJECT_ATTRIBUTE(Texture, "Faces", VariantArray, Variant::Value::VVT_Array, nullptr, static_cast<bool(Texture::*)(const std::vector<std::string>&)>(&Texture::Load));

    auto setWrapMode = [](Texture* iPtr, TextureCoordinate iTC, const std::string& iEnumValue) {
        auto enumValue = textureWrapModeFromString.find(iEnumValue);
        if (enumValue == textureWrapModeFromString.end()) {
            LOGE << "[Texture]: Failed to apply WrapMode, '" << iEnumValue << "' invalid. Ignored." << std::endl;
            return;
        }

        iPtr->SetWrapMode(iTC, enumValue->second);
    };
    CH_OBJECT_ATTRIBUTE_CUSTOM(Texture, "WrapMode U", std::string, Variant::Value::VVT_String, nullptr, [setWrapMode] (Texture* iPtr, const std::string& iEnumValue) {
        setWrapMode(iPtr, TextureCoordinate::TC_U, iEnumValue);
    });
    CH_OBJECT_ATTRIBUTE_CUSTOM(Texture, "WrapMode V", std::string, Variant::Value::VVT_String, nullptr, [setWrapMode] (Texture* iPtr, const std::string& iEnumValue) {
        setWrapMode(iPtr, TextureCoordinate::TC_V, iEnumValue);
    });
    CH_OBJECT_ATTRIBUTE_CUSTOM(Texture, "WrapMode W", std::string, Variant::Value::VVT_String, nullptr, [setWrapMode] (Texture* iPtr, const std::string& iEnumValue) {
        setWrapMode(iPtr, TextureCoordinate::TC_W, iEnumValue);
    });
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

    m_Images[0] = m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImage);

    return _CreateImpl();
}

bool Texture::Load(TextureFace iFace, const std::shared_ptr<Image>& iImage) {
    CH_ASSERT(numberTextureFaces[m_Type] > iFace);

    m_Images[iFace] = iImage;

    return _CreateImpl();
}

bool Texture::Load(TextureFace iFace, const std::string& iImage) {
    CH_ASSERT(numberTextureFaces[m_Type] > iFace);

    m_Images[iFace] = m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImage);

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
        m_Images[i] = m_pContext->GetSubsystem<ResourceLoader<Image>>()->Load(iImages[i]);
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
