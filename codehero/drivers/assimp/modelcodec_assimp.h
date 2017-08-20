// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_ASSIMP_MODELCODEC_ASSIMP_H_
#define CODEHERO_DRIVERS_ASSIMP_MODELCODEC_ASSIMP_H_

#include <string>
#include <vector>
#include "core/resourcecodec.h"

// Forward declaration
struct aiMesh;
struct aiNode;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

namespace CodeHero {

// Forward declaration
class Mesh;
class Model;
class Texture;

class ModelCodecAssimp : public ResourceCodec<Model> {
public:
    OBJECT(ModelCodecAssimp)
    ModelCodecAssimp(const std::shared_ptr<EngineContext>& iContext);

    Error Load(FileAccess& iF, Model& oModel) override;

private:
    void _ProcessNode(aiNode* iNode, const aiScene* iScene, Model& oModel);
    std::shared_ptr<Mesh> _ProcessMesh(aiMesh* iMesh, const aiScene* iScene);
    std::shared_ptr<Texture> _LoadMaterialTextures(aiMaterial* iMat, aiTextureType iType);

    std::string m_ModelDirectory;
};

} // namespace CodeHero

#endif // CODEHERO_DRIVERS_ASSIMP_MODELCODEC_ASSIMP_H_
