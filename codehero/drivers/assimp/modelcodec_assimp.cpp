// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "drivers/assimp/modelcodec_assimp.h"
#include <logger.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "graphics/model.h"
#include "core/enginecontext.h"
#include "core/fileaccess.h"
#include "core/texture.h"
#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "graphics/rendersystem.h"
#include "graphics/material.h"
#include "graphics/mesh.h"
#include "graphics/indexbuffer.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

ModelCodecAssimp::ModelCodecAssimp(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Model>(iContext) {
    std::vector<std::string> ext{"3ds", "blend", "dae", "xml", "fbx", "obj", "raw", "mdl", "mtl"};
    for (auto& e : ext) {
        _AddExtension(e);
    }
}

Error ModelCodecAssimp::Load(FileAccess& iF, Model& oModel) {
    Assimp::Importer import;
    std::string buffer = iF.ReadAll();
    //const aiScene* scene = import.ReadFileFromMemory(buffer.data(), buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs);
    const aiScene* scene = import.ReadFile(iF.GetName(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ConvertToLeftHanded);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOGE << "ModelCodecAssimp: " << import.GetErrorString() << std::endl;
        return FAILED;
    }
    m_ModelDirectory = iF.GetName().substr(0, iF.GetName().find_last_of('/'));

    _ProcessNode(scene->mRootNode, scene, oModel);
    return OK;
}

void ModelCodecAssimp::_ProcessNode(aiNode* iNode, const aiScene* iScene, Model& oModel) {
    // Process all the node's meshes (if any)
    for (uint32_t i = 0; i < iNode->mNumMeshes; ++i) {
        aiMesh* mesh = iScene->mMeshes[iNode->mMeshes[i]];
        oModel.AddMesh(_ProcessMesh(mesh, iScene));
    }

    // Then do the same for each of its children
    for (uint32_t i = 0; i < iNode->mNumChildren; ++i) {
        _ProcessNode(iNode->mChildren[i], iScene, oModel);
    }
}

std::shared_ptr<Mesh> ModelCodecAssimp::_ProcessMesh(aiMesh* iMesh, const aiScene* iScene) {
    std::shared_ptr<Mesh> mesh(new Mesh);

    std::shared_ptr<VertexBuffer> vertex(m_pContext->GetSubsystem<RenderSystem>()->CreateVertexBuffer());
    // Set data first with nullptr in order to get the size of a vertex calculated from the mask
    uint32_t mask = VertexBuffer::MASK_Position;
    if (iMesh->mNormals) {
        mask |= VertexBuffer::MASK_Normal;
    }
    if (iMesh->mTextureCoords[0]) {
        mask |= VertexBuffer::MASK_TexCoord;
    }
    if (iMesh->mTangents) {
        mask |= VertexBuffer::MASK_Tangent;
    }
    if (iMesh->mBitangents) {
        mask |= VertexBuffer::MASK_Bitangent;
    }
    vertex->SetData(nullptr, iMesh->mNumVertices, mask, true);
    size_t vertexSize = vertex->GetComponentsNumber();
    std::vector<float> vertexData(iMesh->mNumVertices * vertexSize);
    size_t dest = 0;
    for (uint32_t i = 0; i < iMesh->mNumVertices; ++i) {
        vertexData[dest++] = iMesh->mVertices[i].x;
        vertexData[dest++] = iMesh->mVertices[i].y;
        vertexData[dest++] = iMesh->mVertices[i].z;
        if (vertex->IsBitActive(VertexBuffer::MASK_Normal)) {
            vertexData[dest++] = iMesh->mNormals[i].x;
            vertexData[dest++] = iMesh->mNormals[i].y;
            vertexData[dest++] = iMesh->mNormals[i].z;
        }
        if (vertex->IsBitActive(VertexBuffer::MASK_TexCoord)) {
            vertexData[dest++] = iMesh->mTextureCoords[0][i].x;
            vertexData[dest++] = iMesh->mTextureCoords[0][i].y;
        }
        if (vertex->IsBitActive(VertexBuffer::MASK_Tangent)) {
            vertexData[dest++] = iMesh->mTangents[i].x;
            vertexData[dest++] = iMesh->mTangents[i].y;
            vertexData[dest++] = iMesh->mTangents[i].z;
        }
        if (vertex->IsBitActive(VertexBuffer::MASK_Bitangent)) {
            vertexData[dest++] = iMesh->mBitangents[i].x;
            vertexData[dest++] = iMesh->mBitangents[i].y;
            vertexData[dest++] = iMesh->mBitangents[i].z;
        }
    }
    vertex->SetSubData(&vertexData[0], 0, iMesh->mNumVertices);
    // Process indices
    std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < iMesh->mNumFaces; ++i) {
        aiFace face = iMesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for (uint32_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    std::shared_ptr<IndexBuffer> indexBuffer(m_pContext->GetSubsystem<RenderSystem>()->CreateIndexBuffer());
    indexBuffer->SetData(&indices[0], indices.size());
    // Process material
    // It seems that condition is not needed. I am removing it. We can add it back if I am wrong
    // if (iMesh->mMaterialIndex >= 0) {
    aiMaterial* aMaterial = iScene->mMaterials[iMesh->mMaterialIndex];
    auto material = std::make_shared<Material>(m_pContext);
    material->SetTexture(TU_Diffuse, _LoadMaterialTextures(aMaterial, aiTextureType_DIFFUSE));
    material->SetTexture(TU_Specular, _LoadMaterialTextures(aMaterial, aiTextureType_SPECULAR));
    // }

    mesh->AddVertexBuffer(vertex);
    mesh->AddIndexBuffer(indexBuffer);
    mesh->SetMaterial(material);

    //return Mesh(vertices, indices, textures);
    return std::move(mesh);
}

std::shared_ptr<Texture> ModelCodecAssimp::_LoadMaterialTextures(aiMaterial* iMat, aiTextureType iType) {
    std::shared_ptr<Texture> texture;
    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();
    // We load only one textures of each type as the engine does not support more... We will have to see
    // what to do here
    for (uint32_t i = 0; i < iMat->GetTextureCount(iType) && i < 1; ++i) {
        aiString str;
        iMat->GetTexture(static_cast<aiTextureType>(iType), i, &str);
        // str should be parsed in case that it is with full path,
        // it should be converted to relative path
        auto path = Split(str.C_Str(), '/');
        if (path.empty() || path.size() == 1) {
            path = Split(str.C_Str(), '\\');
        }
        std::string filename = path.empty() ? "" : path[path.size() - 1];
        texture = rs->CreateTexture();
        texture->Load((m_ModelDirectory + "/" + filename).c_str());
    }
    return texture;
}

} // namespace CodeHero

