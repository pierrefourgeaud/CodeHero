// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_BONE_H_
#define CODEHERO_GRAPHICS_BONE_H_

#include <string>
#include <vector>
#include "core/math/matrix4.h"

namespace CodeHero {

// Forward declaration

class Bone {
public:
    struct WeightPerVertex {
        WeightPerVertex(float iWeight, uint32_t iVertexID)
            : m_Weight(iWeight), m_VertexID(iVertexID) {}
        float m_Weight;
        uint32_t m_VertexID;
    };

    void SetName(const std::string& iName) { m_Name = iName; }
    const std::string& GetName() const { return m_Name; }

    void SetVerticesWeight(const std::vector<WeightPerVertex>& iVerticesWeight) {
        m_VerticesWeight = iVerticesWeight;
    }
    const std::vector<WeightPerVertex>& GetVerticesWeight() const { return m_VerticesWeight; }

    void AddWeightPerVertex(const WeightPerVertex& iWeightPerVertex) {
        m_VerticesWeight.push_back(iWeightPerVertex);
    }
    // TODO(pierre) What should we do as Getters ? GetPerVertexID ? GetPerIndex ?

    void SetOffsetMatrix(const Matrix4& iOffsetMatrix) { m_OffsetMatrix = iOffsetMatrix; }
    const Matrix4& GetOffsetMatrix() const { return m_OffsetMatrix; }

private:
    std::string m_Name;
    Matrix4 m_OffsetMatrix;

    std::vector<WeightPerVertex> m_VerticesWeight;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_BONE_H_
