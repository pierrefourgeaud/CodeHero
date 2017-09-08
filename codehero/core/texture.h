// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TEXTURE_H_
#define CODEHERO_CORE_TEXTURE_H_

#include <glad/glad.h>
#include <array>
#include <memory>
#include "core/gpuobject.h"
#include "core/image.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

enum TextureCoordinate {
    TC_U = 0,
    TC_V,
    TC_W,
    TC_MaxCoords
};

enum TextureWrapMode {
    TWM_Repeat = 0,
    TWM_MirroredRepeat,
    TWM_ClampEdge,
    TWM_MirroredClampEdge,
    TWM_ClampBorder,
    TWM_MaxWrapModes
};

enum TextureFace {
    TF_Main2D = 0, // Used for 2D textures
    // Next 6 are used in Cubemaps
    TF_PosX = TF_Main2D,
    TF_NegX = 1,
    TF_PosY = 2,
    TF_NegY = 3,
    TF_PosZ = 4,
    TF_NegZ = 5,
    TF_MaxCubeMap = 6
};

static const uint32_t numberTextureFaces[] = {
    1, // T_2D
    6  // T_CUBE
};

class Texture : public GPUObject {
public:
    enum Type {
        T_2D = 0,
        T_Cube,
        T_Max
    };

    Texture(std::shared_ptr<EngineContext>& iContext, Type iType);
    virtual ~Texture();

    virtual void Bind(int32_t iUnit = -1) = 0;
    virtual void Unbind() = 0;
    bool Load(const std::shared_ptr<Image>& iImage);
    bool Load(const char* iImage);
    bool Load(TextureFace iFace, const std::shared_ptr<Image>& iImage);
    bool Load(TextureFace iFace, const char* iImage);
    bool Load(const std::vector<std::shared_ptr<Image>>& iImages);
    bool Load(const std::vector<const char*>& iImages);

    void SetWrapMode(TextureCoordinate iCoordinate, TextureWrapMode iWrapMode);

    Type GetType() { return m_Type; }

protected:
    Type m_Type;
    std::array<TextureWrapMode, TC_MaxCoords> m_WrapCoordinates{ TextureWrapMode::TWM_Repeat };

    virtual bool _CreateImpl() = 0;

    const std::shared_ptr<Image>& _GetImage(TextureFace iFace = TF_Main2D) const { return m_Images[iFace]; }

private:
    std::shared_ptr<EngineContext> m_pContext;
    std::vector<std::shared_ptr<Image>> m_Images;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TEXTURE_H_
