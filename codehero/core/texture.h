// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TEXTURE_H_
#define CODEHERO_CORE_TEXTURE_H_

#include <array>
#include <map>
#include <memory>
#include "core/gpuobject.h"
#include "core/image.h"
#include "core/serializable.h"

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

static const std::map<std::string, TextureWrapMode> textureWrapModeFromString = {
    {"TWM_Repeat", TWM_Repeat},
    {"TWM_MirroredRepeat", TWM_MirroredRepeat},
    {"TWM_ClampEdge", TWM_ClampEdge},
    {"TWM_MirroredClampEdge", TWM_MirroredClampEdge},
    {"TWM_ClampBorder", TWM_ClampBorder}
};

enum TextureFace : uint32_t {
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

class Texture : public Serializable, public GPUObject {
public:
    OBJECT(Texture, Serializable)

    enum Type {
        T_2D = 0,
        T_Cube,
        T_Max
    };

    Texture(std::shared_ptr<EngineContext>& iContext);
    virtual ~Texture();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Texture> Create(const std::shared_ptr<EngineContext>& iContext);

    virtual void Bind(int32_t iUnit = -1) = 0;
    virtual void Unbind() = 0;
    bool Load(const std::shared_ptr<Image>& iImage);
    bool Load(const std::string& iImage);
    bool Load(TextureFace iFace, const std::shared_ptr<Image>& iImage);
    bool Load(TextureFace iFace, const std::string& iImage);
    bool Load(const std::vector<std::shared_ptr<Image>>& iImages);
    bool Load(const std::vector<std::string>& iImages);

    void SetWrapMode(TextureCoordinate iCoordinate, TextureWrapMode iWrapMode);

    void SetType(Type iType);
    Type GetType() const { return m_Type; }

protected:
    Type m_Type = T_2D;
    std::array<TextureWrapMode, TC_MaxCoords> m_WrapCoordinates{ TextureWrapMode::TWM_Repeat };

    virtual bool _CreateImpl() = 0;

    const std::shared_ptr<Image>& _GetImage(TextureFace iFace = TF_Main2D) const { return m_Images[iFace]; }

private:
    std::vector<std::shared_ptr<Image>> m_Images;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TEXTURE_H_
