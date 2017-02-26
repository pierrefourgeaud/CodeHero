// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "drivers/assimp/modelcodec_assimp.h"
#include <logger.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "graphics/model.h"
#include "core/math/vector2.h"
#include "core/math/vector3.h"

namespace CodeHero {

ModelCodecAssimp::ModelCodecAssimp() {
    std::vector<string> ext{"3ds", "blend", "dae", "xml", "fbx", "obj", "raw", "mdl"};
    for (auto e& : ext) {
        _AddExtension(e);
    }
}

Error ModelCodecAssimp::Load(FileAccess& iF, Model& oModel) {
    Assimp::Importer import;
    std::string buffer = iF.ReadAll();
    const aiScene* scene = import.ReadFileFromMemory(buffer.data(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOGE << "ModelCodecAssimp: " << import.GetErrorString() << std::endl;
        return Failed;
    }
    //this->directory = path.substr(0, path.find_last_of('/'));

    _ProcessNode(scene->mRootNode, scene);
}

void ModelCodecAssimp::_ProcessNode() {
    // Process all the node's meshes (if any)
    for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }

    // Then do the same for each of its children
    for (uint32_t i = 0; i < node->mNumChildren; ++i) {
        this->processNode(node->mChildren[i], scene);
    }
}

void ModelCodecAssimp::_ProcessMesh() {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        // Texture Coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        } else {
            vertex.TexCoords = {0.0f, 0.0f};
        }
        vertex.Tangent = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
        vertex.Bitangent = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
        vertices.push_back(vertex);
    }
    // Process indices
    for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for (uint32_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    // Process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = _LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = _LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

vector<Texture> ModelCodecAssimp::_LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (uint32_t i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), this->directory);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}

} // namespace CodeHero

